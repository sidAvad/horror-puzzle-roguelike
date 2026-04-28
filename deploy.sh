#!/bin/bash
set -e

echo "Building WASM..."
./build.sh

echo "Deploying to GitHub Pages..."

cp -r build/web /tmp/game-build

git stash --include-untracked 2>/dev/null || true

git checkout gh-pages
rm -rf *
cp -r /tmp/game-build/* .
rm -rf /tmp/game-build

git add -A
git commit -m "deploy: $(date '+%Y-%m-%d %H:%M:%S')"
git push origin gh-pages

git checkout main
git stash pop 2>/dev/null || true

echo ""
echo "Deployed! Live in ~30 seconds at:"
echo "   https://sidavad.github.io/horror-puzzle-roguelike"
echo "Refresh Safari on your iPhone"
