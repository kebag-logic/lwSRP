# SPDX-License-Identifier: Apache-2.0
"""Check local paths, local heading fragments, and unique external URLs."""

import argparse
from concurrent.futures import ThreadPoolExecutor
import sys
from urllib.error import HTTPError, URLError
from urllib.parse import unquote, urlsplit
from urllib.request import Request, urlopen

sys.dont_write_bytecode = True
from common import LINK, ROOT, anchors, pages, sections


def external(url):
    try:
        request = Request(url, headers={"User-Agent": "documentation-link-check/1.0"})
        with urlopen(request, timeout=30) as response:
            status = response.status
            return url, status, 200 <= status < 400
    except HTTPError as error:
        return url, error.code, False
    except (URLError, TimeoutError, OSError) as error:
        return url, str(error), False


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--local-only", action="store_true", help="Skip external requests explicitly")
    args = parser.parse_args()
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
                    if target.suffix != ".md" or unquote(parts.fragment) not in anchors(target):
                        reason = "missing heading"
                if reason:
                    errors += 1
                    print(f"FAIL {path.relative_to(ROOT)}:{number}: {href}: {reason}")
    if not args.local_only:
        with ThreadPoolExecutor(max_workers=4) as pool:
            for url, status, okay in pool.map(external, sorted(urls)):
                print(f"{'PASS' if okay else 'FAIL'} {url}: {status}")
                errors += not okay
    else:
        print(f"SKIP external URLs: {len(urls)}; requested local-only check")
    print(f"Local links: {local_count}; external URLs: {len(urls)}; failures: {errors}")
    return int(errors != 0)


if __name__ == "__main__":
    raise SystemExit(main())
