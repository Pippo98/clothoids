#!/usr/bin/env bash
# Regenerate bindings/py/py_clothoids/_core.pyi (the type stub used by IDEs
# for autocompletion). Run it after changing bindings.cpp and commit the result.
set -euo pipefail

root="$(cd "$(dirname "$0")/../.." && pwd)"
tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT

python3 -m venv "$tmp/venv"
"$tmp/venv/bin/pip" install --quiet --disable-pip-version-check "$root" pybind11-stubgen

# Run outside the repo so the installed package is the one imported
cd "$tmp"
"$tmp/venv/bin/python" -m pybind11_stubgen py_clothoids._core \
  --exit-code -o "$tmp/stubs"
cp "$tmp/stubs/py_clothoids/_core.pyi" "$root/bindings/py/py_clothoids/_core.pyi"
echo "Updated bindings/py/py_clothoids/_core.pyi"
