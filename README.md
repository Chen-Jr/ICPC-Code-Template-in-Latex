# ICPC-Code-Template-in-Latex


创建一个Latex版本的 ACM-ICPC 模板。

本项目主要以github的另一个项目：https://github.com/jasison27/ACM-ICPC-CodeTemplate-Late 为基础，进行了一定程度上的修改于完善：

- 优化了排版
- 优化了全文的代码显示
- 支持中文
- 可以在每一个Subciton/Subsection/Subsubsection后插入`.tex`文件，用来对当前的模板进行说明。
- 支持subsubsection的建立。

## 文件结构：

![12](https://raw.githubusercontent.com/Chen-Jr/ICPC-Code-Template-in-Latex/master/%E7%BB%93%E6%9E%84.png)

其中：

1. 主文件中的 `config`文件为控制一级目录的配置文件，主要用来控制Section的输出。内部填写的名字代表着一个一级目录。该项需要使用者自行进行更改。
2. 主文件中的 `head`、`tail`、`main.cpp`文件**不建议**进行修改，直接使用即可。如果有意对生成的`tex`文件进行自定义修改，可以修改`head`以及`tail`文件。如果发现编译运行`main.cpp`文件时发生错误，可以根据`main.cpp`中的注释进行一定程度上的修改。
3. 一级目录中的`config`文件为当前目录的配置文件，主要用来控制Subsection的输出及判定是否存在Subsubsection。该文件存在四个参数：
<二级目录名称> <代码文件> <tex文件> <三级目录名称>
   - <二级目录名称>：在<>内部填写当前你需要的二级目录（即Subsection）的名称
   - <代码文件>：在<>内部填写在当前二级目录中，你所需要插入的代码(支持`.java`/`.cpp`/`.py`文件)。**如果当前状态下无需代码，则在<>中间留空（如果没有后面两个参数，则可以直接省略<>）**，
   - <tex文件>：在<>内部填写在当前二级目录中，你所需要插入的说明文件`.tex`.**如果当前状态下无需代码，则在<>中间留空（如果没有最后一个参数，则可以直接省略<>）**
   - <三级目录名称>：如果你需要生成一个三级目录，则你只需要在在次项中填写于<二级目录名称>相同的名称。**注意：此时填写的名字代表的是一个二级目录，（是一个文件夹），此时第二个以及第三个参数需要留空**
4. 二级目录中的`config`文件配置跟上述相同，只需要照葫芦画瓢即可。

## 使用：

### 准备：

ACM-ICPC模版库、g++环境、Latex发行版软件

#### Linux：

直接make就可以了（如果没有安装Latex，需要自行安装一下texlive-full）

#### Windows：

**因为需要支持中文，故需要将Windows系统编码改为utf-8！！**

之后编译运行`main.cpp`，之后就会生成一份`template.tex`文件，最后只需要用Latex使用`XeLatex`编译生成pdf文件即可。
