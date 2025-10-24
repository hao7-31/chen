import std/strutils
import nimib
import ./theme/codeOutput  # 若有自定义代码主题模块可保留，否则可移除

var nbToc: NbBlock

template addToc =
  newNbBlock("nbText", false, nb, nbToc, ""):
    nbToc.output = "## 目录:\n\n"

template nbNewSection(name: string) =
  let anchorName = name.toLower.replace(" ", "-")
  nbText "<a name=\"" & anchorName & "\"></a>\n<br>\n### " & name & "\n\n---"
  nbToc.output.add "1. <a href=\"#" & anchorName & "\">" & name & "</a>\n"

template nbSubSection(name: string) =
  let anchorName = name.toLower.replace(" ", "-")
  nbText "<a name=\"" & anchorName & "\"></a>\n<br>\n#### " & name & "\n\n---"
  nbToc.output.add "    * <a href=\"#" & anchorName & "\">" & name & "</a>\n"

template nbQuoteBlock(code: untyped) =
  nbText "<blockquote>"
  code
  nbText "</blockquote>"

nbInit # ----------------------------- START ----------------------------------
initCodeTheme()  # 若有自定义代码主题初始化逻辑可保留


nbText: """
《RPN 计算器说明文档》
======================================

- 作者：[你的名字]
- 版本：1.0.0
- 修订、nimib 移植：[你的名字]

## 引言

RPN（逆波兰表示法）计算器是一种基于栈操作的计算工具，它通过“操作数入栈，运算符作用于栈顶元素”的逻辑完成计算，避免了传统中缀表达式的括号依赖，在工程计算、编程领域有着广泛应用。

本文档将详细介绍 RPN 计算器的原理、使用方法及实现细节，帮助您快速掌握这一实用工具。

"""

addToc()

nbNewSection "RPN 计算原理"

nbText: """
逆波兰表示法（RPN）是一种将运算符放在操作数之后的表达式表示方法。例如，中缀表达式 `3 + 4` 在 RPN 中表示为 `3 4 +`。其核心计算逻辑基于**栈结构**：

1. 遇到操作数时，将其压入栈中；
2. 遇到运算符时，从栈中弹出足够数量的操作数（如二元运算符弹出两个），执行运算后将结果压回栈中；
3. 表达式结束时，栈顶元素即为最终结果。
"""

nbCodeSkip:
  # 以 "3 4 + 5 *" 为例，计算过程如下：
  # 栈变化：[3] → [3,4] → [7] → [7,5] → [35]
  echo "最终结果为 35"

nbText: """
这种设计的优势在于无需解析括号优先级，计算流程更直观，也更易通过程序实现。
"""

nbNewSection "RPN 计算器的使用方法"

nbSubSection "基本操作"

nbText: """
启动 RPN 计算器后，您可以通过输入操作数和运算符来执行计算。以下是基本操作示例：
"""

nbCodeSkip:
  # 计算 (2 + 3) * 4
  # 输入：2 3 + 4 *
  # 步骤：
  # 2 入栈 → 3 入栈 → + 运算（2+3=5 入栈）→ 4 入栈 → * 运算（5*4=20 入栈）
  echo "结果：20"

nbText: """
输入完成后，栈顶元素即为计算结果。您可以继续在当前栈的基础上输入新的操作数和运算符，实现连续计算。
"""

nbSubSection "常用运算符"

nbText: """
本计算器支持以下常用运算符：
- `+`：加法，如 `1 2 +` 结果为 `3`；
- `-`：减法，如 `5 3 -` 结果为 `2`；
- `*`：乘法，如 `4 5 *` 结果为 `20`；
- `/`：除法，如 `8 2 /` 结果为 `4`；
- `^`：幂运算，如 `2 3 ^` 结果为 `8`；
- `sqrt`：平方根，如 `16 sqrt` 结果为 `4`（单操作数，弹出栈顶元素计算后压回）。
"""

nbNewSection "RPN 计算器的实现（Nim 代码）"

nbText: """
以下是一个简单 RPN 计算器的 Nim 实现代码，它通过栈结构处理输入的表达式：
"""




nbSave # ----------------------------- END ------------------------------------

