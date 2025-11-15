from collections import deque
# Finds the occurrences of a set of patterns in a text simultaneously
# $O(n + m + matches)$, where n = len(text), m = total pattern length.
class TrieNode:
    def __init__(self):
        self.children = {}
        self.output = []
        self.fail = None
def build_automaton(keywords):
    root = TrieNode()
    for keyword in keywords:
        node = root
        for char in keyword:
            node = node.children.setdefault(char, TrieNode())
        node.output.append(keyword)
    queue = deque()
    for node in root.children.values():
        node.fail = root
        queue.append(node)
    while queue:
        current = queue.popleft()
        for ch, nxt in current.children.items():
            queue.append(nxt)
            f = current.fail
            while f and ch not in f.children:
                f = f.fail
            nxt.fail = f.children[ch] if f else root
            nxt.output += nxt.fail.output
    return root
def search_text(text, keywords):
    root = build_automaton(keywords)
    res = {kw: [] for kw in keywords}
    node = root
    for i, ch in enumerate(text):
        while node and ch not in node.children:
            node = node.fail
        if not node:
            node = root
            continue
        node = node.children[ch]
        for kw in node.output:
            res[kw].append(i - len(kw) + 1)
    return res
