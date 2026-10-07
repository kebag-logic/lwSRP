<!-- SPDX-License-Identifier: Apache-2.0 -->
# Documentation checks

These checks support authors, reviewers, and testers.
Run them from the repository root with [Python](https://docs.python.org/3/).
The scripts use its standard library.
Install [Mermaid CLI](https://github.com/mermaid-js/mermaid-cli) for graph rendering.
Its browser dependency must also be available.

Set DOC_SCRATCH to a writable directory outside the checkout before rendering.
Keep generated images and dependency installations there.

~~~sh
python3 doc/tools/check_sentences.py
python3 doc/tools/check_references.py
python3 doc/tools/check_references.py --self-test
python3 doc/tools/check_links.py --github-auth
python3 doc/tools/render_mermaid.py --output "$DOC_SCRATCH/graphs"
~~~

| Check | Scope and result |
| --- | --- |
| [Sentence checker](check_sentences.py) | Joins wrapped paragraphs and checks sentences, list items, headings, and table cells. |
| [Reference checker](check_references.py) | Finds unlinked standards, clauses, files, issues, API identifiers, and known documentation tools. |
| [Link checker](check_links.py) | Checks relative paths, local headings, source line ranges, and external responses. |
| [Graph renderer](render_mermaid.py) | Extracts graphs, counts nodes, renders each graph, and reports each command's exit code. |
| [Shared parser](common.py) | Scans root and documentation Markdown pages, including inline code in prose. |

All checks return zero on success and nonzero on failure.
No broken link is silently exempted.
The required [licence](../../LICENSE) and [notice](../../NOTICE) links fail until the separate licence change is present.
External access failures remain failures.

While the repository is private, the link command uses authenticated access for repository URLs only.
Sign in with the [GitHub CLI](https://cli.github.com/manual/) before running it.
The checker derives the repository from the HTTPS origin remote and labels each authenticated result.
It checks issue-comment fragments through the comment endpoint.
Unsupported repository URLs fail explicitly.
All other external URLs use anonymous HTTP requests.
After publication, omit the authentication option to verify anonymous access.

The sentence and reference checks list every fenced block as a syntax exception.
Commands, graph labels, and code need literal syntax.
Their file, API, standard, and tool references belong in nearby links.
[SPDX](https://spdx.dev/) comments are metadata.
There are no prose sentence exemptions.

The parser supports the inline links and fences used by these pages.
It does not implement every Markdown extension.
The reference finder is a heuristic; reviewers must also read the prose.
Its self-test checks bare standard names, inline code, linked references, and identifier boundaries.
The graph counter supports these pages' explicit nodes and participants.
Rendering checks syntax.
Review the resulting images for readable labels and clear layout.

An optional browser configuration can be passed through the renderer's help-documented option.
Keep that environment-specific configuration outside the checkout.
