## 创建git仓库
1. 在github中点击new新建
2. 输入仓库名称
3. 选择私有或公开
4. 是否创建README.md文件(在本地仓库上传时创建会出错)
5. gitignore:选择不上传都文件如node_modules
6. license不知道有什么用


## 增加内容
1. 添加文件
``` bash
git add <file1> <file2>
```
添加当前目录下所有文件
``` bash
git add .
```
2. 提交文件
``` bash
git commit -m <message>
```
git commit命令，-m后面输入的是本次提交的说明，可以输入任意内容，当然最好是有意义的，这样你就能从历史记录里方便地找到改动记录。
3. 输入用户名和邮箱
``` bash
git config --global user.name kkssf
git config --global user.email 1273526910@qq.com
```

## 创建本地仓库及提交内容
1. 先创建一个空的目录，右击选择 Git Bash Here
``` bash
git init
```
2. 将本地库和远程库关联
``` bash
git remote add origin git地址
```
3. 将本地分支内容提交到远程
``` bash
git push -u origin master
```

## 常用指令
1. 查看版本库的状态,已发生过新建或者修改的文件
` git status`
2. 查看提交历史
` git log`
3. 版本设定
` git reset --hard head^^`
` git reset --hard head~2`
4. 查看历史版本
` git reflog `
5. 查看文件内容
` cat readme.txt`
6. 克隆到本地电脑
` git clone`
7. 创建新的分支
` git branch 分支名称`
8. 切换分支
` git checkout`
9. 提交到远程仓库
` git push –u origin 分支名称`