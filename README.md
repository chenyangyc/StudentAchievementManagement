# StudentAchievementManagement
### An achievements management system for students, developed in C++14.

### 学生成绩管理系统

#### 1. 实现功能（含发散功能）


1. 从文件中读取并写入学生信息（姓名、学号、课程数目、各课程名称及其成绩）
2. 手动添加学生信息（键盘输入）
3. 修改学生课程的成绩（根据姓名或学号，出现重名时会根据学号让用户再做一次选择）
4. 查询学生信息（根据姓名或学号，出现重名时会根据学号让用户再做一次选择）
5. 删除学生的信息（根据姓名或学号，出现重名时会根据学号让用户再做一次选择）
6. 计算并存储学生的加权成绩，平均绩点，总学分
7. 查看加权成绩的年级排名
8. 查看单科成绩的年级排名
9. 查看所有学生的信息（姓名，学号，平均绩点，拥有的所有课程的名称、学分、成绩和绩点，加权成绩，总学分）
10. 查看所有科目的信息（名称，学分，年级平均成绩，年纪平均绩点）
11. 本地存储学生及其课程和成绩的信息

#### 2. 项目目录

1. ##### **`Course`**类

   - 此类即为课程类，保存各个科目的课程名称，学分，成绩和对应绩点等。
   - 定义并实现了对于课程的一些操作，如计算绩点和根据名称搜索等。同时由于对一些成员变量进行了封装，也含有相应的`get`和`set`方法。
   - 采用`builder`设计模式，即使用`CourseBuilder`创建`Course`类的对象
   - 重载了`>`操作符，使得`Course`类可以成为`map`的value类型

2. ##### **`CourseBuilder`**类

   - 使用`CourseBuilder`链式构造`Course`类的对象，避免了臃肿冗长的构造函数，增强代码可读性。
   - 可以满足实例化部分特性不同的同类对象的要求。

3. ##### **`Student`**类

   - 此类为学生类，保存各个学生的学号，姓名，课程数目，拥有的课程信息和成绩等信息。
   - 持有`Course`类的`vector`, 存储学生拥有的课程的信息
   - 定义并实现了对学生的一些操作，如搜索学生`searchStudentByKeyword`，计算绩点`setGpa`，计算加权成绩`setWeightedScore`，搜索拥有的单门课程及其成绩`getSingleCourse`、`getSingleCourseScore`等。同时也有对被封装变量的`get`和`set`方法
   - 使用`StudentBuilder`创建`Student`类的对象

4. ##### **`StudentBuilder`**类

   同**`CourseBuilder`**类

5. ##### **`Management`**类

   - 此类继承了`ManageMethods`的接口并重写实现了其中的方法，含有实现成绩管理系统功能的主要功能函数
   - 持有`Student`类的`vector`，用来存储对所有学生的信息
   - 持有`Course`类的`vector`，用来存储年级所有课程的信息

6. ##### **`ManageMethods`**(抽象类，做接口用)

   - `Management`的基类， 定义了成绩管理系统主要功能函数的接口。

#### 3. 实现细节

##### Summary：大致思路为

`Course`类存储课程的信息，实现对课程的一些操作（gpa,查询等）

`Student`持有`vector<Course>`，存储单个学生拥有的课程，并在本类中实现对学生及其拥有课程的操作函数

`Management`持有``vector<Student>``，存储所有的学生，持有`vector<Course>`，存储年级所有的课程。继承`ManageMethods`, 通过调用`Course` 和`Student`类的方法和自己实现的方法实现成绩管理系统的主要功能函数。

其中值得称道的是`Course`和`Student`均采用`builder`建造者模式来链式创建对象，避免了出现冗余的构造函数

##### Details:

- **开发工具：CLion ， 基于C++ 14。由于中文注释和程序中的中文交互提示文字，部分文件采用`GBK`编码，编码格式不同可能导致打开出现乱码，注意编码格式。**

- **部分采用了`C++11`引入的`base-ranged-loop`，即**

  ```c++
  vector<Student> students;
  for(Student& student: students){
  	//TODO：operations;
  }
  ```

  **这相当于**

  ```c++
  vector<Student> students;
  for(int i = 0; i < students.size(); i++){
  	//TODO：operations;
  }
  //上例中的student即相当于这里的student[i]
  ```

  **若是由于环境或编译器问题出现编译错误, 请老师联系我进行修改。**

- 已经预设好了`StudentInfo.txt`文件，第一次打开即可正常读入信息并使用。但需注意读取文件通过函数`loadFile`实现，该文件只需处于函数指定的目录下即可正常被读取，**注意txt文件最后一行不应该是空行。**

- 添加学生信息通过`addStudent`实现，输入学生的课程信息时课程名称、学分和成绩支持以空格或回车分隔。

- 查询学生通过`searchStudentByKeyword`实现，它调用了`Student`类中的`searchStudentById`和`searchStudentByName`，通过学号和姓名皆可查询。

- 修改成绩通过`alterScore`实现，先调用`查询`功能得到需要被修改的学生信息(重名时会根据学号再做判断)，再调用`Student`类中的`getSingleCourse`得到想要修改的科目

- 删除学生信息先调用`查询`得到要删除的学生，然后将其从`Management`持有的`vector<Student>`中删除

- 计算学生成绩和绩点等均为`Student`类中提供的方法

- 判断重名通过`judgeRepeatedName`函数实现，大致思路为遍历搜索返回的vector，返回指向学号对应的学生对象的指针

- 查看单科排名时通过`Student`类持有的`vector<Course>`和`getSingleScore`得到课程成绩，然后通过`pair`和`map`实现三元组存储学生信息和对应课程成绩，重写`vector`的`sort`函数进行排序。加权排名基本同理

- 查看所有科目信息时通过`Management`持有的`vector<Course>`得到年级所有课程的信息

- 本地存储文件通过`storeFile` ，按照特定格式向指定路径的`txt`文件进行写入

- 三元组存储的方式也可通过重载操作符，使`Student`和`Course`分别成为map的键和值来替代，不知孰优孰劣

- 个人成绩，加权排名和单科排名随成绩修改而实时改变，单科年级平均成绩需要重新加载txt文件刷新后才可更新

- 每次运行程序时会先读入预设的`txt`文件，因此需保证文件格式正确，否则会出现读入错误

#### 4， 优化总结

- `Course`，`Student`和`Management`耦合度较低，逻辑更为清晰，修改和增加功能也更为方便
- 采用`builder`模式，增加可读性和代码的复用性，避免冗余代码（不过由于Dos界面，很多逻辑近似的交互由于提示文字不同，未能进行良好的封装，略显臃肿）
- 选择性的对一些变量进行了良好的封装，不过感觉良好的封装性和代码简洁度之间的平衡还是很难找的XD
- 针对大多数可能的错误输入进行了提醒和处理，可以对重名的情况做处理，增强了代码健壮性
- 定义接口类便于修改和应对需要的新需求，增加复用性
- 已有预设好的`StudentInfo.txt`，可参照文件格式进行修改测试（最后一行不是空行）

#### 5. github仓库地址：

- 成绩管理系统： <https://github.com/Desirelife6/MFC_StudentAchievementManagement.git>
