# 学生管理系统


### 开发环境：visual studio 2019版本


### 功能：

1. 登录界面：
   1. 提供登录接口和注册接口
   2. 登录时查系统保存的文件，如没有该用户名或密码错误只能重试
   3. 注册只能成为用户权限，且用户名不能与已知用户重合，有匿名输入功能，要求注册时重复输入密码，
2. 用户界面：
   1. 提供按ID查找和按姓名查找功能，都是找到了则返回全部信息，没有找到则输出“Not Found”
3. 管理员界面：
   1. 提供对学生增删改查，对用户账号增删改查接口
   2. 对学生：
      1. 查：比用户界面内多了查看所有学生信息的功能
      2. 增：可以创建学生信息，比如按照规定格式输入，格式错误会报错重新输入
      3. 删：先查询删除学生信息，如果有则列出，再删除，没有则“Not Found”退出
      4. 改：可以修改学生的成绩信息，按规定输入，输入错误报错
   3. 对用户：
      1. 增：可以增加非重复的用户名，在这里面可以直接将用户注册为管理员权限
      2. 删：删除用户
      3. 改：可以修改密码和管理员权限。按提示修改哪一个。
      4. 查：查找用户
4. 退出接口：
   1. 所有的界面只有按界面提示的exit退出，输入的数据才能保存，如果没有按照提示正常退出，则操作的数据将不被写入文件。



### 文件
会由系统传入用户信息和学生信息，argc和argv校验失败则报错。创建文件database.dat和userinfo.dat，如果使用visual studio，需要提前设置命令行参数，否则会报错。
