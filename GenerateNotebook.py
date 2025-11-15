import os
import re

TEMPLATE_FILE = "template.tex"      
OUTPUT_FILE = "notebook.tex"

SECTIONS = [
    ("Number Theory", "number"),
    ("Data Structures", "data"),
    ("Graph Algorithms", "graph"),
    ("Strings", "strings"),
    ("Arrays", "array"),
    ("Utilities", "utilities")
]

IGNORE_PATTERNS = [
    r'^\s*#include',
    r'^\s*using\s+namespace', 
    r'^\s*typedef(?!\s+struct)' 
]

IGNORE_PATTERNS_PYTHON = [
    r'^\s*(import|from)\b'
]

COMMENT_RE = re.compile(r'^\s*//\s*(.*)$') 
COMMENT_RE_PY = re.compile(r'^\s*#\s*(.*)$')

def process_cpp_file(path):
    lines = []
    code_block = []

    with open(path) as f:
        for line in f:
            raw = line.rstrip()

            if any(re.match(p, raw) for p in IGNORE_PATTERNS):
                continue

            m = COMMENT_RE.match(raw)
            if m:
                if(code_block):
                    lines.append("\\begin{minted}{cpp}\n" + "\n".join(code_block) + "\n\\end{minted}\n")
                    code_block = []
                lines.append(m.group(1) + "\n")
            elif raw != "":
                code_block.append(raw)

    if code_block:
        lines.append("\\begin{minted}{cpp}\n" + "\n".join(code_block) + "\n\\end{minted}\n"+
                     r"\noindent\makebox[\columnwidth]{\rule{\columnwidth}{0.4pt}}")

    return "".join(lines)


def process_python_file(path):
    lines = []
    code_block = []

    with open(path) as f:
        for line in f:
            raw = line.rstrip()

            if any(re.match(p, raw) for p in IGNORE_PATTERNS_PYTHON):
                continue

            m = COMMENT_RE_PY.match(raw)
            if m:
                if code_block:
                    lines.append("\\begin{minted}{python}\n" +
                                 "\n".join(code_block) +
                                 "\n\\end{minted}\n")
                    code_block = []
                lines.append(m.group(1) + "\n")
            elif raw != "":
                code_block.append(raw)

    if code_block:
        lines.append("\\begin{minted}{python}\n" +
                     "\n".join(code_block) +
                     "\n\\end{minted}\n" +
                     r"\noindent\makebox[\columnwidth]{\rule{\columnwidth}{0.4pt}}")

    return "".join(lines)

with open(TEMPLATE_FILE) as f:
    template = f.read()

content = []

for title, folder in SECTIONS:
    content.append(f"\\section{{{title}}}\n")
    for fname in sorted(os.listdir(folder)):
           
        if not (fname.endswith(".cpp") or fname.endswith(".py")):
            continue

        path = os.path.join(folder, fname)

        if fname.endswith(".cpp"):
            code_content = process_cpp_file(path)
            content.append(f"\\subsection{{{fname[:-4]}}}\n")
        else: 
            code_content = process_python_file(path)
            content.append(f"\\subsection{{{fname[:-3]}}}\n")

        content.append("".join(code_content))

full_text = template.replace("%CONTENT%", "\n".join(content))

with open(OUTPUT_FILE, "w") as f:
    f.write(full_text)

print(f"Notebook generated: {OUTPUT_FILE}")


