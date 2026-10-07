# SPDX-License-Identifier: Apache-2.0
"""Check local paths, local heading fragments, and unique external URLs."""

import argparse
from concurrent.futures import ThreadPoolExecutor
from functools import partial
import re
import subprocess
import sys
from urllib.error import HTTPError, URLError
from urllib.parse import unquote, urlsplit
from urllib.request import Request, urlopen

sys.dont_write_bytecode = True
from common import LINK, ROOT, anchors, pages, sections


def repository_endpoint(url, repository):
    """Map supported repository links to API endpoints without sending credentials elsewhere."""
    parts = urlsplit(url)
    prefix = f"/{repository}"
    if parts.scheme != "https" or parts.netloc != "github.com":
        return None
    if parts.path != prefix and not parts.path.startswith(prefix + "/"):
        return None
    suffix = parts.path[len(prefix):].rstrip("/")
    if parts.fragment:
        comment = re.fullmatch(r"issuecomment-(\d+)", parts.fragment)
        if comment and re.fullmatch(r"/(?:issues|pull)/\d+", suffix):
            return f"repos/{repository}/issues/comments/{comment[1]}"
        return ""
    if suffix == "" or re.fullmatch(r"/(?:issues|pulls)(?:/\d+)?", suffix):
        return f"repos/{repository}{suffix}"
    if re.fullmatch(r"/pull/\d+", suffix):
        return f"repos/{repository}/pulls/{suffix.rsplit('/', 1)[1]}"
    return ""


def authenticated_repository():
    result = subprocess.run(
        ["git", "remote", "get-url", "origin"], capture_output=True, text=True, timeout=30, check=True
    )
    match = re.fullmatch(r"https://github\.com/([\w.-]+/[\w.-]+?)(?:\.git)?", result.stdout.strip())
    if not match:
        raise ValueError("Authenticated checks require an HTTPS origin on github.com")
    return match[1]


def external(url, repository=None):
    try:
        endpoint = repository_endpoint(url, repository) if repository else None
        if endpoint is not None:
            if not endpoint:
                return url, "authenticated: unsupported repository URL", False
            result = subprocess.run(
                ["gh", "api", "--hostname", "github.com", endpoint, "--silent"],
                capture_output=True, text=True, timeout=60,
            )
            return url, f"authenticated; API rc={result.returncode}", result.returncode == 0
        request = Request(url, headers={"User-Agent": "documentation-link-check/1.0"})
        with urlopen(request, timeout=30) as response:
            status = response.status
            return url, f"anonymous; HTTP {status}", 200 <= status < 400
    except HTTPError as error:
        return url, f"anonymous; HTTP {error.code}", False
    except (URLError, TimeoutError, OSError, subprocess.TimeoutExpired) as error:
        return url, str(error), False


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--local-only", action="store_true", help="Skip external requests explicitly")
    parser.add_argument("--github-auth", action="store_true", help="Authenticate origin repository links with the GitHub CLI")
    args = parser.parse_args()
    if args.local_only and args.github_auth:
        parser.error("--local-only and --github-auth are mutually exclusive")
    repository = None
    if args.github_auth:
        try:
            repository = authenticated_repository()
        except (OSError, ValueError, subprocess.SubprocessError) as error:
            parser.error(str(error))
    errors = 0
    local_count = 0
    urls = set()
    for path in pages():
        for kind, number, text in sections(path):
            if kind != "prose":
                continue
            for match in LINK.finditer(text):
                href = match[2]
                parts = urlsplit(href)
                if parts.scheme in ("http", "https"):
                    urls.add(href)
                    continue
                if parts.scheme or parts.netloc:
                    errors += 1
                    print(f"FAIL {path.relative_to(ROOT)}:{number}: unsupported link {href}")
                    continue
                local_count += 1
                target = (path.parent / unquote(parts.path)).resolve() if parts.path else path
                reason = ""
                if not target.is_relative_to(ROOT):
                    reason = "outside repository"
                elif not target.exists():
                    reason = "missing target"
                elif parts.fragment:
                    fragment = unquote(parts.fragment)
                    lines = re.fullmatch(r"L([1-9]\d*)(?:-L([1-9]\d*))?", fragment)
                    if lines and target.is_file():
                        first = int(lines[1])
                        last = int(lines[2] or lines[1])
                        if not first <= last <= len(target.read_text(encoding="utf-8").splitlines()):
                            reason = "invalid line range"
                    elif target.suffix != ".md" or fragment not in anchors(target):
                        reason = "missing heading"
                if reason:
                    errors += 1
                    print(f"FAIL {path.relative_to(ROOT)}:{number}: {href}: {reason}")
    if not args.local_only:
        with ThreadPoolExecutor(max_workers=4) as pool:
            for url, status, okay in pool.map(partial(external, repository=repository), sorted(urls)):
                print(f"{'PASS' if okay else 'FAIL'} {url}: {status}")
                errors += not okay
    else:
        print(f"SKIP external URLs: {len(urls)}; requested local-only check")
    print(f"Local links: {local_count}; external URLs: {len(urls)}; failures: {errors}")
    return int(errors != 0)


if __name__ == "__main__":
    raise SystemExit(main())
