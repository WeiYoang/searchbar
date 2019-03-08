#                                       Searchbar
* 功能
###      在一篇文章，一本书中根据给出的单词罗列出含有该单词的句子。
* 安装
#### 对于linux或macos用户

#### $cd searchbar

#### $cd ./install.sh

* 使用
### 一般模式（normal model）
#### $searchbar filepath word
### 调试模式 （debug model）
##### 显示用于检索的红黑树以中序遍历。
#### $searchbar -r filepath

* 注意
#### 由于个人时间关系，此程序没有完全写完，缺少文本文件的预处理程序即格式化，因为在设计时将标点符号看作单词而每个单词之间应该有空格，比如下列例子：
##### We all have dreams , and you are no exception .
* 结尾
#### 最后在提两点，因为没有不完美，所以在执行安装脚本程序后，本程序并没有导入用户shell环境中，因此使用时应该是./searchbar, 因为这个格式化程序几乎是独立，所以任何人有兴趣去完成它，还请request me. 我将非常乐意 pull it into my programming.
