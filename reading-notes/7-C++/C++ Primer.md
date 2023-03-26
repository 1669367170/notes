# 《C++ Primer第五版》笔记

视频链接：https://www.bilibili.com/video/BV1z64y1U7hs/?p=36&spm_id_from=333.880.my_history.page.click&vd_source=5ca8c9858efdf576a9c470964f99463a

其他笔记参考链接：https://github.com/applenob/Cpp_Primer_Practice

## P7 类

### 7.1 定义抽象数据类型

1、类的基本思想是**数据抽象（接口与实现分离）和封装（把实现隐藏起来）**。

2、this是一个**指针常量**（包含类对象本身的地址），不允许改变指针里的地址。this的类型是(Sales_data* const)。

- 【底层const】常量指针：const int *PtrConst；// **指向常量的指针**

  底层const：指向的或者绑定的是const。不能通过解引用指针的方式，修改变量的值。称指针为常量的指针。

- 【顶层const】指针常量：int* const ConstPtr = &a；// 必须初始化，**指针本身是常量**

  顶层const：对象本身是const。指针在定义初始化之外，不能被赋值修改。称指针为指针常量。

3、定义一个返回this对象的函数

```C++
// 模拟复合运算符+=，为了和+=一致，返回为左值。
Sales_data& Sales_data::combine(const Sales_data &rhs) // right hand side
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this; // 返回调用该函数的对象
}
```

4、IO对象不能拷贝，只能引用。

5、拷贝、赋值和析构构造函数，如果没有定义，编译器将会提供合成的默认版本（default）。

**管理动态内存（new）的类，通常不能依赖于编译器合成的版本。（使用vector或string除外）**

---

### 7.2 友元

6、友元：允许其他类或函数（比如非类成员函数）访问自己的非公有成员。（友元不是类的一部分）

```C++
class Screen {
    // Window_mgmr的成员可以访问Screen类的私有部分
    friend class Window_mgmr;
    // 不对整个类开放，只对clear函数开放
    friend void Window_mgmr::clear(ScreenIndex);
}
```

令成员函数作为友元时，注意顺序：

- 定义Window_mgmt类，声明clear函数，**但不能定义它**；
- 定义Screen，包括对于clear的友元声明；
- 定义clear，此时才能使用Screen的成员。

---

### 7.3 类的其他特性

7、类的内部进行成员函数的定义，相当于隐式内敛（inline）。**也可以在类外进行定义，函数头加inline设为内联函数**。

8、可变数据成员：mutable。即使在一个const对象内也能被修改。

```c++
class Screen {
public:
    void some_member() const; // 对于const成员函数来说，this指针是const的，指向常量的指针。
private:
    mutable size_t access_ctr; // 即使在一个const对象内也能被修改
}

void Screen::some_member() const
{
    ++access_ctr;
}
```

9、类的前向申明

- 类的声明可以和定义分离，前向声明，在定义之前是一个不完整类型。（不能用于定义一个对象，因为需要知道对象占多大的空间）

- **不完整类型可以定义指向该类型的指针或引用，也可以作为函数声明中的参数或返回类型。**

```C++
class Screen; // 类的前向声明

class Link_screen {
    Screen window; // 错误，不完整类型
    Link_screen *next; // 正确，一旦类名字出现后，就被认为是声明过了
    Link_screen *prev;
}
```

---

### 7.4 类的作用域

10、类型名的定义应该放到类的开始处。

```C++
typedef double Money;
class Acount {
public:
    Money balance() { return bal; } // 使用外层作用域的Money
private:
    typedef double Money; // 错误，重复定义，编译器并不负责
    Money bal;
}
```

11、类的成员函数在实现定义时，用到的类/函数等，必须已经完成声明。

---

### 7.5 构造函数再探

12、如果成员是const、引用或者属于某种未提供默认构造函数的类类型，必须通过构造函数初始化列表提供初始值。

const和引用不属于赋值。

13、**构造函数初始值列表的顺序，不会影响实际的初始化顺序。**

```C++
class X {
    int i;
    int j;
    
public:
    X(int val) : j(val), i(j) {} // error, 按照定义顺序，i在j之前被初始化。
}
```

14、委托构造函数：把自己的一些（或全部）职责给了其他构造函数。

15、如果构造函数支持一个实参的调用，那么也就定义了从参数类型向类类型隐式转换的规则 （只允许一步类类型转换）-> explicit（抑制，一步也不允许隐式转换，explicit定义后只能用于直接初始化不能用于拷贝形式初始化）

16、聚合类：（可以使用初始值列表初始化，顺序要注意）

- 所有成员都是public
- 没有定义任何构造函数
- 没有类内初始值
- 没有基类，也没有virtual函数

17、字面值类（constexpr）

### 7.6 类的静态成员

18、static函数不包含this指针，所以不能定义成const函数。

19、静态成员不占用对象的内存。存在于任何对象之外，所有对象共享。

20、static关键字出现在类内部的声明语句中，外部定义不要static关键字。（内部声明，外部定义）

21、静态数据类型可以是不完全类型。（**static成员、指针都可以是不完全类型，对象必须是完全类型，需要知道分配多少空间**）

22、可以使用静态成员作为默认实参，因为它本身并不是对象的一部分。

## P8 C++标准库：IO类

### 8.1 IO类

23、IO库类型和头文件（w表示wchar_t）

| 头文件   | 类型                                                         |
| -------- | ------------------------------------------------------------ |
| iostream | istream, wistream 从流中读取；ostream, wostream 写到流中去；iostream, wiostream 对流进行读写 |
| fstream  | ifstream, wifstream 从文件中读取；ofstream, wofstream 写到文件中去；fstream, wfstream 读写文件 |
| sstream  | istringstream, wistringstream 从string对象中读取；ostringstream, wostringstream 写到string对象中去；                          stringstream, wstringstream 对string对象进行读写 |

24、IO对象不能拷贝或赋值。

25、IO库条件状态。

### 8.2 文件输入输出

26、每个流文件都有一个关联的**文件模式**（fille mode）

|             | 文件模式                                 |
| ----------- | ---------------------------------------- |
| in          | 以读方式打开                             |
| out         | 以写方式打开                             |
| app(append) | 追加：每次写操作前均定位到文件末尾       |
| ate(at end) | 每次打开文件后立即定位到末尾             |
| trunc       | 截断：如果打开的文件存在，其内容将被丢弃 |
| binary      | 以二进制方式进行IO                       |

### 8.3 string流

27、IO类继承关系

```mermaid
graph TD
iostream --> ostream & istream & stringstream & fstream
istream --> ifstream & istringstream
ostream --> ofstream & ostringstream
```

28、

```C++
sstream strm(s); // strm是一个sstream对象，保存string s的一个拷贝。此构造函数是explicit的。
strm.str(); // 返回strm所保存的string的拷贝。
strm.str(s); // 将string s拷贝到strm中。
```

29、string代表的是内存，istringstream是从内存读取数据，ostringstream是将数据写入内存。

## P9 C++标准库：容器

### 9.1 顺序容器概述

30、C++的容器分为顺序容器、关联容器。

**每种容器都是性能和功能的权衡（添加、删除、非顺序访问）**

31、常见顺序容器

| 头文件       | 类型                                                         |
| ------------ | ------------------------------------------------------------ |
| vector       | 可变大小数组。支持快速随机访问。在尾部之外的位置插入或删除元素可能很慢。 |
| deque        | 双端队列。**支持快速随机访问。在头尾位置插入/删除速度很快。** |
| list         | 双向链表。只支持双向顺序访问。在list中任何位置进行插入/删除操作速度都很快。 |
| forward_list | 单向链表。只支持单向顺序访问。在链表任何位置进行插入/删除操作速度都很快。 |
| array        | 固定大小数组。支持快速随机访问。不能添加或删除元素。（作用是替换内置数组如int a[]） |
| string       | 和vector相似的容器，但专门用于保存字符。随机访问快。在尾部插入/删除速度快。 |

32、开始不确定用哪种容器，首选vector。注意使用容器的公共操作比如：迭代器而不是下标。后面若扩展迁移到其他容器，代码可以复用。

### 9.2 容器库概述

33、迭代器范围一般是由一对迭代器表示（左闭合区间）：[begin, end)。

34、一个容器初始化为另一个容器的拷贝时，容器类型和元素类型必须相同。

35、内置数组不支持拷贝或赋值。

```C++
int digs[5] = {0, 1, 2, 3, 4};
int cpy[5] = digs; // error
```

36、容器赋值运算

```C++
c1 = c2 // c1中元素替换成c2中元素的拷贝，c1和c2必须有相同的类型
c = {a, b, c, ..} // 将c1中元素替换成初始化列表中元素的拷贝(array不适用)
swap(c1, c2) // 交换c1和c2中的元素。通常比c2向c1拷贝元素快得多。（相关的地址换了一下）
c1.swap(c2)
    
assign操作不适用于关联容器和array
seq.assign(b, e) // 将seq中的元素替换成迭代器b和e所表示的范围中的元素。迭代器b和e不能指向seq中的元素。
seq.assign(i1) // 将seq中的元素替换成初始化列表i1中的元素。
seq.assign(n, t) // 将seq中的元素替换为n和值为t的元素。
```

- **赋值相关运算会导致指向左边容器内部的迭代器、引用和指针失效。**
- 而swap操作将容器内容交换不会导致指向容器的迭代器、引用和指针失效（容器类型为array和string的情况除外）。array还是会进行拷贝。
- 赋值运算后，两者的大小都与后边容器的原大小相同。
- array不支持assign，也不允许花括号包围的值列表进行赋值。
- assign允许从一个不同但相容的类型赋值，或是从容器的一个子序列赋值。

37、容器关系运算操作

``` C++
vector<int> v1 = {1,3,5,7,9,12};
vector<int> v2 = {1,3,9}
vector<int> v3 = {1,3,5,7}
v1 < v2; // true
v1 < v3; // false
```

关系运算符左右两边必须类型相同。只有当其元素类型也定义了相应的比较运算符时，我们才可以使用关系运算符来比较两个容器。

### 9.3 顺序容器操作

38、向顺序容器添加元素

- **向一个vector、string或deque插入元素，会使得所有指向容器的迭代器、指针和引用失效**。

- ```C++
  c.insert(p,t) // 在迭代器p指向的元素之前创建一个值为t的元素。返回指向新添加元素的迭代器。
  c.insert(p,n,t) // 在迭代器p指向的元素之前插入n个值为t的元素。返回指向新添加的第一个元素的迭代器。
  c.insert(p,a.begin(),a.end())
  ```

- 可以通过insert实现：将元素插入到vector、deque和string中的任何位置，都是合法的。然而这样做可能很耗时。

- **使用emplace操作：构造元素而不是拷贝元素**。

39、在顺序容器中访问元素的操作

```C++
1）at和下标操作只适用于string、vector、deque和string。back不适用于forward_list。
2）c.back()和c.front()：返回c中尾/首元素的引用。若c为空，函数行为未定义。
3）c[n],c.at(n)：返回下标为n的元素的引用。
```

40、顺序容器的删除操作

```C++
1）这些操作会改变容器的大小，所以不适用于array。
2) forward_list有特殊版本的erase，不支持pop_back；vector和string不支持pop_front。
3）c.pop_back()/c.pop_front() // 删除c中尾、首元素，若c为空则函数行为未定义，函数返回void。
4）c.erase(p) // 删除迭代器p所指定的元素，返回一个指向被删除元素之后元素的迭代器。
5）c.erase(b,e) // 删除迭代器b和e所指定范围的元素。返回迭代器是e。删除范围是左闭合区间：[b,e)
6）c.clear()
```

- **删除deque中除首尾之外的任何元素都会使得迭代器、引用和指针都失效。指向vector或string中删除点之后位置的迭代器、引用和指针都会失效**。

41、特殊的forward操作

- 单向链表没有简单的方法来获取一个元素的前驱。
- before_begin(); // 获取单向链表首前的位置。 
- insert_after(); emplace_after(); // 返回一个指向最后一个插入元素的迭代器。
- erase_after(); // 返回一个指向被删元素之后元素的迭代器。

42、顺序容器大小操作

```C++
resize不适用于array
c.resize(n) // 调整c的大小为n个元素。若n<c.size()，则多出的元素被丢弃。若必须添加新元素，则对新元素进行值初始化。
c.resize(n,t) // 调整c的大小为n个元素。任何新添加的元素都初始化为值t。
```

- **如果resize缩小容器，则指向被删除元素的迭代器、引用和指针都会失效；对vector、string或deque进行resize可能导致迭代器、指针和引用失效。**
- resize可调整容器元素个数。

43、不要缓存end符合的迭代器，如auto end = v.end()是会存在问题的操作。（比如删除元素或增加元素扩容的情况）

### 9.4 vector对象是如何增长的

44、容器大小管理操作

```C++
shrink_to_fit只适用于vector、string和deque。
capacity和reserve只适用于vector和string。
c.shrink_to_fit(); // 请将capacity()减少为与size()相同大小
c.capacity(); // 不重新分配内存空间的化，c可以保存多少元素
c.reserve(n); // 分配至少能容纳n个元素的内存空间
```

- **capacity（容量）和size（有多少个元素）含义不一样**。

  0 | 1 | 2 | 3 | ... | 23 | 保留空间 |

  ​                       ↑size                 ↑capacity

- **reserve并不改变容器中元素的数量，它仅影响vector预分配多大的内存空间（容量）**。 

- vector扩容一般是翻一倍，具体看编译器版本实现。

### 9.5 额外的string操作

45、额外的构造函数

```C++
n, len2和pos2都是无符号值
string s(cp,n) // s是cp指向的数组中前n个字符的拷贝。此数组至少应该包含n个字符。
string s(s2,pos2) // s是string s2从下标pos2开始的字符的拷贝。若pos2>s2.size()，构造函数的行为未定义。
string s(s2,pos2,len2) // s是string s2从下标pos2开始len2个字符的拷贝。若pos2>s2.size()，构造函数的行为未定义。不管len2的值是多少，构造函数最多拷贝s2.size()-pos2个字符。
```

46、子字符串操作

```C++
s.substr(pos,n) // 返回一个string，包含s中从pos开始的n个字符的拷贝。pos的默认值为0。n的默认值为s.size()-pos，即拷贝从pos开始的所有字符。
```

47、插入操作

```C++
c.insert(s.size(), 5, '!'); // 在s末尾插入5个感叹号
c.erase(s.size()-5, 5); // 在s删除最后5个字符

// C风格字符数组的insert和assign版本
const char *cp = "Stately, plump Buck";
s.assign(cp, 7); // s = "Stately"
s.insert(s.size(), cp+7); // s = "Stately, plump Buck"

// 我们也可以指定来自其他string或字符串的字符插入到当前string中
string s = "some string", s2 = "some other string";
s.insert(0, s2); // 在s中位置0之前插入s2的拷贝
s.insert(0, s2, 0, s2.size()); // 在s[0]之前插入s2中s2[0]开始的s2.size()个字符
```

48、append和replace函数

```C++
// append操作是在string末尾进行插入操作的一种简写形式
string s("C++ Primer"), s2 = s;
s.insert(s.size(), "4th Ed.") // s = "C++ Primer 4th Ed."
s2.append("4th Ed."); // 等价方法， s=s2
// replace操作是调用erase和insert的一种简写形式
// 将"4th"替换为"5th"的等价方法
s.erase(11, 3); // s = "C++ Primer Ed."
s.insert(11, "5th"); // s = "C++ Primer 5th Ed."
// 从位置11开始，删除3个字符并插入"5th"
s2.replace(11, 3, "5th"); // 等价方法：s = s2
// s.replace(11, 3, "Fifth"); 也可以，长度无需一样
```

49、string搜索操作

```C++
// 搜索操作返回指定字符出现的下标，如果未找到则返回npos。
s.find(args) // 查找s中args第一次出现的位置
s.rfind(args) // 查找s中args最后一次出现的位置
s.find_first_of(args) // 在s中查找args中任何一个字符第一次出现的位置
s.find_last_of(args) // 在s中查找args中任何一个字符最后一次出现的位置
s.find_first_not_of(args) // 在s中查找第一个不在args中的字符
s.find_last_not_of(args) // 在s中查找最后一个不在args中的字符
    
// 每个函数都有4个重载版本
    args必须是以下形式
c, pos		// 从s中位置pos开始查找字符c。pos默认为0
s2, pos		// 从s中位置pos开始查找字符串s2。pos默认为0
cp, pos		// 从s中位置pos开始查找指针cp指向的以空字符结尾的C风格字符串。pos默认为0
cp, pos, n  // 从s中位置pos开始查找指针cp指向的数组的前n个字符。pos和n无默认值
```

- 每个搜索操作都返回一个string::size_type值。

- 判断搜索到结尾：string::npos。

50、s.compare的几种参数形式

```C++
s2 // 比较s和s2
pos1, n1, s2 // 将s中从pos1开始的n1个字符与s2进行比较
pos1, n1, s2, pos2, n2 // 将s中从pos1开始的n1个字符与s2中从pos2开始的n2个字符进行比较
    
cp // 比较s与cp指向的以空字符结尾的字符数组
pos1, n1, cp // 将s中从pos1开始的n1个字符，与cp指向的以空字符结尾的字符数组进行比较
pos1, n1, cp, n2 // 将s中从pos1开始的n1个字符与指针cp指向的地址开始的n2个字符进行比较
```

51、string和数值之间的转换

```C++
to_string(val) 	// 一组重载函数，返回数值val的string表示
// 返回s的起始子串（表示整数内容）的数值，返回类型分别是int,long,unsigned long,long long, unsigned long long，b表示转换所用的基数，默认值是10。p是size_t指针，用来保存s中第一个非数值字符的下标，p默认为0，即函数不保存下标。
stoi(s,p,b)
stol
stoul
stoll
stoull
// 返回s的起始字串（表示浮点数内容）的数值，返回值类型分别是float,double或long double。参数p的作用与整数转换函数中一样。
stof(s,p) 
stod(s,p)
stold(s,p)
    
std::string s2 = "pi=3.14!!!"
d = stod(s2.substr(s2.find_first_of("+-.0123456789")));
// d = stod(s2.substr(3)) -> d = stod("3.14!!!") -> d = 3.14
```

### 9.6 容器适配器

52、三个顺序容器适配器：stack、queue和priority_queue。

53、所有的适配器都要求容器具有添加、删除以及方便访问尾元素的能力。

54、所有容器适配器都支持的操作和类型

```C++
size_type	// 一种类型，足以保存当前类型的最大对象的大小。
value_type	// 元素类型
container_type	// 实现适配器的底层容器类型
A a;		// 创建一个名为a的空适配器
A a(c);		// 创建一个名为a的适配器，带有容器c的一个拷贝
关系运算符	 // 每个适配器都支持所有关系运算符：==、!=、<、<=、>和>=，这些运算符返回底层容器的比较结果
a.empty()
a.size()
swap(a,b)	// 交换a和b的内容，a和b必须有相同类型，包括底层容器类型也必须相同
a.swap(b)
```

55、栈默认基于deque实现，也可以在list或vector之上实现。

```C++
s.pop()	// 删除栈顶元素，但不返回该元素值
s.push(item) // 创建一个新元素压入栈顶，该元素通过拷贝或移动item而来，或者由args构造
s.emplace(args)
s.top() // 返回栈顶元素，但不将元素弹出栈
```

56、队列queue默认基于deque实现，priority_queue默认基于vector实现。queue也可以用list或vector实现，priority_queue也可以用deque实现。

```C++
q.pop() // 删除queue的首元素或priority_queue的最高优先级的元素，但不返回。
q.front() // 返回首元素或尾元素，但不删除该元素
q.back() // 只适用于queue
q.top() // 返回最高优先级元素，但不删除该元素，只适用于priority_queue
q.push(item) // 在queue末尾或priority_queue中恰当的位置创建一个元素，其值为item，或由args构造
q.emplace(args)
```

## P10 泛型算法

### 10.1 泛型算法概述

- 泛型的：可以用于不同类型的容器和不同类型的元素。
- 容器中定义的操作非常有限，其他操作（例如：**查找特定元素、替换或删除一个特定元素、排序**等）都是通过一组泛型算法来实现的。
- 大多数算法都定义在头文件algorithm中。头文件numeric还定义了一组算法。

```C++
int val = 42; // 将查找的值
auto result = find(vec.begin(), vec.end(), val);
std::cout << "val: " << val << (result == vec.end()? "存在" : "不存在") << std::endl;
```

- **泛型算法本身不会执行容器的操作，只会运用于迭代器上。 **

### 10.2 初始泛型算法

标准库提供了超过100个算法

57、只读算法

```C++
// 对vec中的元素求和，和的初值为0（第三个参数还决定了返回类型，以及+的使用）
int sum = accumulate(vec.begin(), vec.end(), 0);

// 接受单一迭代器来表示第二个序列的算法，都假设第二个序列至少与第一个序列一样长
// 第三个参数表示第二个序列的首元素
// roster1可以是vector<string>, roster2可以是list<const char *>，不要求同样容器，只要能够访问和比较即可。
equal(roster1.cbegin(), roster1.cend(), roster2.begin()); 
```

58、写容器元素的算法

```C++
fill(vec.begin(), vec.end(), 0); // 将每个元素重置为0
// 将容器的一个子序列设置为10
fill(vec.begin(), vec.begin() + vec.size/2, 10);

vector<int> vec;
// 第二个参数：要填充多少个元素
fill_n(vec.begin(), vec.size(), 0); // 将所有元素重置为0
fill_n(dest,n,val); // dest是起点，指向一个元素，而从dest开始至少需要包含n个元素
```

59、插入迭代器

- back_inserter，是定义在头文件iterator中的一个函数，接受指向容器的引用，返回绑定该容器的插入迭代器。
- **所有泛型算法都是通过迭代器操作的，不能调用容器的push_back等来增加元素**。

```C++
vector<int> vec;
auto it = back_inserter(vec); // 通过它赋值会将元素添加到vec中
*it = 42; // vec中现在有一个元素，值为42

vector<int< vec2;
// 正确：back_inserter创一个插入迭代器，可用来向vec添加元素
// 每次赋值，会在迭代器上调用push_back，改变了容器的元素个数
fill_n(back_inserter(vec2),10,0); // 添加10个元素到vec2
```

60、拷贝算法

```C++
int a1[] = {0,1,2,3,4,5,6,7,8,9};
int a2[sizeof(a1)/size(*a1)]; // a2与a1大小一样，*a1是首元素a1[0]
auto ret = copy(begin(a1),end(a1),a2); // 把a1的内容拷贝给a2

// 将所有值为0的元素改为42
replace(list.begin(),list.end(),0,42);

// 使用back_inserter按需要增长目标序列
replace_copy(ilist.begin(),ilist.end(),back_inserter(ivec),0,42);
// 上面的语句调用后，ilist并未改变，ivec包含ilist的一份拷贝
// 不过原来在ilist中值为0的元素在ivec中都变成了42
```

61、重排容器元素的算法

```C++
// 消除重复单词
void elimDups(vector<string> &words)
{
    // 按字典顺序排序
    sort(words.begin(), words.end());
    // unique消除相邻的重复项，unique函数把不重复的元素放在前面，把重复的放在后面
    // 排序在范围的前部，返回指向不重复区域之后一个位置的迭代器
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}
```

### 10.3 lambda表达式、bind函数

62、定制操作 

```C++
// sort默认使用元素类型的<运算符

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}
// 按长度由短至长排序words，sort可以接受一个二元谓词参数
sort(words.begin(), words.end(), isShorter);
```

上面的sort函数的第三个参数是一个谓词：

- 谓词是一个可调用的表达式
- 返回结果是一个能用做条件的值
- 谓词分为一元谓词和二元谓词
- **谓词必须与算法相匹配，如果要多于2个参数，可考虑用lambda表达式或bind函数**

stable_sort稳定排序算法，维持相等元素的原有顺序。

63、lambda表达式

- 可调用的代码单元，一个未命名的内联函数。

```C++
[capture list] (parameter list) -> return type { function body }
```

- 当以引用方式捕获一个变量时，必须保证在lambda执行变量时存在的。

- 隐式捕获：让编译器根据lambda体中的代码来推断需要使用哪些变量。

  1）若隐式是引用，则后面是拷贝方式的列表。[&, identifier_list]

  2）若前面隐式是拷贝方式列表，则后面是引用方式的列表。[=, reference_list]

  3）隐式在前面，显式在后面。

64、可变lambda

```C++
void func3() {
    size_t v1 = 42;
    auto f = [v1]()mutable {return ++v1;}
    v1 = 0;
    auto j = f(); // j is 43
}
```

多条谓语句，要添加尾置返回类型。（不然无法推断return类型）

```C++
std::transform(vi.begin(), vi.end(), vi.begin()
              [](int)->int
               {if(i<0) return -i; else return i;});
// 将vi容器里面的数做一个转换（取绝对值），再放回vi容器。
```

65、参数绑定

- 调用bind的一般形式为：auto newCallable = bind(callable, arg_list)。
- 定义在function头文件中。
- **一般什么时候用bind函数**：一个函数（比如泛型算法），第三个参数要放一个可调用对象，**但可调用对象只支持一个参数，而真正要用到多于2个参数，可以用lambda表达式。但lambda表达式比较适合仅用一次或两次，如果这个可调用对象经常要用，可以使用bind函数。**

```C++
using namespace std;
using namespace std::placeholders;

vector<string> words = {"string1", "abcde"};
bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}

int main()
{
    // check6是一个可调用对象，接受一个string类型的参数
    // 并用此string和值6来调用check_size
    auto check6 = bind(check_size, _1, 6);
    string s = "hello";
    bool b1 = check6(s); // check6(s)会调用check_size(s, 6);
}
```

```C++
[bind的参数]
// g是一个有2个参数的可调用对象
auto g = bind(f,a,b,_2,c,_1);
// g(X,Y)的调用会映射到：f(a,b,Y,c,X)

[用bind重排参数位置]
// 按单词长度由短至长排序
sort(words.begin(), words.end(), isShorter);
// 按单词长度由长至短排序
sort(words.begin(), words.end(), bind(isShorter, _2, 1));
// 当sort需要比较两个元素A和B时，调用isShorter(A,B)
// 当sort比较两个元素时，就好像调用了isShorter(B,A)一样

[绑定引用参数] 默认情况下，bind的那些不是占位符的参数会被拷贝
// 错误：不能拷贝os
for_each(words.begin(), words.end(), bind(print, os, _1, ''));
// 对于ostream对象，不能拷贝。必须使用标准库的ref函数包含给定的引用
for_each(words.begin(), words.end(), bind(print, ref(os), _1, ''))
```

### 10.4  再探迭代器

66、插入迭代器

插入迭代器有3种类型：

- back_inserter，创建一个使用push_back的迭代器；c.push__back(t)

- front_inserter，创建一个使用push_front的迭代器；c.push_front(t)

  ```C++
  list<int> lst = {1,2,3,4}
  list<int> lst2, lst3;
  // front_inserter生成的迭代器，总是指向容器的第一个元素。
  
  // 拷贝完成后，lst2包含4,3,2,1
  copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
  // 拷贝完成后，lst3包含1,2,3,4; lst3.begin()不会重新计算。
  copy(lst.cbegin(), lst.cend(), inserter(lst3,lst3.begin()));
  ```

- inserter，创建一个使用insert的迭代器，插入指定迭代器之前的位置。c.insert(p,t)

- *it, ++it, it++：这些操作虽然存在，但不会对it做任何事情，每个操作都返回it。

  ```C++
  *it = val; // it是由inserter生成的迭代器，效果与下面代码一样
  
  it = c.insert(iter, val); // it指向新插入的元素
  ++it; // 递增it，使得它指向原来的元素位置。
  ```

67、流迭代器

将对应的流，当做一个特定类型的元素序列来处理。

- istream_iterator操作

```C++ 
istream_iterator<T> in(is); // in从输入流is读取类型为T的值
istream_iterator<T> end;    // 读取类型为T的值的istream_iterator迭代器，表示尾后位置
in1 == in2					// in1和in2必须读取相同类型。如果它们都是尾后迭代器，或绑定到相同的输入，则两者相等
in1 != in2
*in							// 返回从流中读取的值
in->mem						// 与(*in).mem的含义相同
++in, in++					// 使用元素类型所定义的>>运算符从输入流中读取下一个值。与以往一样，前置版本返回一个指向递增迭代器的引用，后置版本返回旧值。
```

- ostream_iterator操作

```C++
ostream_iterator<T> out(os); // out将类型为T的值写到输出流os中
ostream_iterator<T> out(os,d); // out将类型为T的值写到输出流os中，每个值后面都输出一个d。d指向一个空字符结尾的字符数组。
out = val; // 用<<运算符将val写入到out所绑定的ostream中。val的类型必须与out可写的类型兼容。
*out, ++out, out++ // 这些运算符是存在的，但不对out做任何事情。每个运算符都返回out。
```

68、 反向迭代器

```C++
sort(vec.begin(), vec.end()); // 按"正常序"排序vec，升序
sort(vec.rbegin(), vec.rend()); // 按逆序排序；将最小元素放在vec的末尾，降序
```

- 反向迭代器需要递减运算符，所以forward_list或流迭代器不能创建反向迭代器。

### 10.5 泛型算法结构

- 算法所要求的5个迭代器类别

| 输入迭代器     | 只读，不写。单遍扫描，只能递增       |
| -------------- | ------------------------------------ |
| 输出迭代器     | 只写，不读。单遍扫描，只能递增       |
| 前向迭代器     | 可读写，多遍扫描，只能递增           |
| 双向迭代器     | 可读写，多遍扫描，可递增递减         |
| 随机访问迭代器 | 可读写，多遍扫描，支持全部迭代器运算 |

- 类似容器，迭代器的操作也分层次。高层类别的迭代器支持所有底层类别迭代器的操作。

- 算法形参模式

  大多数算法具有以下4种形式之一：

  1）alg(beg, end, other args);	2）alg(beg, end, dest, other args);

  3）alg(beg, end, beg2, other args); 4）alg(beg, end, beg2, end2, other args);

- 算法命名和重载规范 

  规定如何提供一个操作替代默认的运算符，以及算法将输出数据写入输入序列还是一个分离目的地的问题。

  ```C++
  // 将相邻重复元素删除
  unique(beg,end); // 使用==运算符比较元素
  unique(beg,end,comp); // 使用comp比较元素
  
  find(beg,end,val); // 在范围内查找特定元素第一次出现的位置
  find_if(beg,end,pred); // 查找第一个令pred为true的元素
  
  reverse(beg,end); // 翻转输入范围中元素的顺序
  reverse_copy(beg,end,dest); // 将元素逆序拷贝到dest
  
  // 从vi中删除奇数元素
  remove_if(v1.begin(), v1.end(), [](int i){ return i % 2; });
  // 将偶数元素从v1拷贝到v2，v1不变
  remove_copy_if(v1.begin(), v1.end(), back_inserter(v2), [](int i){ return i % 2; });
  ```

### 10.6 特定容器算法

69、list和forward_list成员函数版本的算法

```C++
lst.merge(lst2); // lst1和lst2都必须式有序的，将来自lst2中的元素合并入lst。
lst.merge(lst2, comp); // 元素将从1st2中删除。在合并之后，lst2变为空。第一个版本使用<运算符；第二个版本使用给定的比较操作。
lst.remove(val); // 调用erase删除掉与给定值相等（==）或令一元谓词为真的每个元素。
lst.remove_if(pred);
lst.reverse(); // 反转lst中元素的顺序
lst.sort(); // 使用<或给定比较操作排序元素
lst.sort(comp);
lst.unique();
lst.unique(pred); // 调用erase删除同一个值的连续拷贝。第一个版本使用==；第二个版本使用给定的二元谓词。
```

- 对于list和forward_list，应该优先使用成员函数版本的算法而不是通用算法。
- 链表特有的版本会改变底层的容器。

70、list和forward_list的splice成员函数参数（插入功能）

```C++
lst.splice(args)或flst.splice_after(args)
```

- splice算法是链表结构所特有的

## P11 关联容器

### 11.1 使用关联容器

- 顺序容器：元素按在容器中的位置保存和访问的。关联容器：元素是按关键字来保存和访问的。
- multimap：关键字可重复出现的map；multiset：关键字可重复出现的set。

### 11.2 关联容器概述

71、关键字类型要求：

有序容器：map、multimap、set、multiset关键字类型必须定义元素的比较的方法。**如果一个类型定义了"行为正常"的<运算符，则可以用作关键字类型。**

### 11.3 关联容器操作

- 类型别名

```C++
key_type 此容器类型的关键字类型
mapped_type 每个关键字关联的类型：只适用于map
value_type 对于set，与key_type相同；对于map，为pair<const key_type, mapped_type>
```

- map、set、multimap、multiset迭代器按关键字升序遍历元素。
- 通常不对关联容器使用泛型算法。   

- 添加元素

```C++
auto ret = word_count.insert({word, 1}); // ret.first: 指向具体给定关键字的元素; ret.second: 指出元素是否插入成功
```

- 删除元素

```C++
c.erase(b, e); // 删除迭代器对b和e所表示的范围中的元素。返回e
```

- 查找元素

```C++
low_bound和upper_bound不适用于无序容器。（multixxx的上界和下界    ）
c.lower_bound(k); // 返回一个迭代器, 指向第一个关键字不小于k的元素
c.upper_bound(k); // 返回一个迭代器, 指向第一个关键字大于k的元素
c.equal_range(k); // 返回一个迭代器pair, 表示关键字等于k的元素的范围。若k不存在, pair的两个成员均等于c.end() 

for(auto beg = authors.low_bound(item); end = authors.upper_bound(item); beg != end; ++beg)
{
	// [beg, end)    
}
// 以下相同方式
for(auto pos = authors.equal_range(item); pos.first != pos.end(); ++pos.first)
{
    
}
```

### 11.4 无序容器

72、无序容器：不使用比较运算符来组织元素，而是使用哈希函数和关键字类型的==运算符。

73、管理桶：无序容器的性能依赖于哈希函数的质量和桶的数量大小。

无序容器管理操作：桶接口、桶迭代、哈希策略。

74、无序容器默认情况下：

- **使用关键字类型的==运算符比较元素；**
- **用一个hash<key_type>类型的对象来生成每个元素的哈希值；**
- 标准库为内置类型（包括指针），string，智能指针提供了hash模板。

75、定义关键字类型为自定义类型的无序容器

```C++
// 为了将Sale_data用作关键字，我们需要提供：
// 1、函数来代替==运算符
// 2、哈希函数
size_t hasher(const Sales_data &sd)
{
    return hash<string>()(sd.isbn()); // 利用标准库hash类型对象来计算
}

bool eqOp(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}

using SD_multiset = unordered_multiset<Sales_data, decltype(hasher)*, decltype(eqOp)*>
// 参数是（桶大小、哈希函数指针、相等性判断运算指针）
SD_multiset bookstore(42, hasher, eqOp);
// 假设Foo有==运算符
unordered_set<Foo, decltype(FooHash)*> foodSet(10, FooHash);
```

## P12 智能指针

### 12.1 动态内存和智能指针

#### 12.1.1 shared_ptr

- 栈对象：仅在其定义的程序块运行时才存在。（严格的生存期）

- static对象：在使用之前分配，在程序结束时销毁。（严格的生存期）

- 堆对象：动态分配的对象，在程序运行过程中可以随时建立或删除的对象。

- **智能指针是模板。默认初始化的智能指针里面保存着一个空指针。**

- shared_ptr和unique_ptr都支持的操作

  ```c++
  p.get() // 返回p中保存的指针。要小心使用，若智能指针释放了其对象，返回的指针所指向的对象也就消失了。
  swap(p, q) // 交换p和q中的指针
  ```

- shared_ptr独有的操作

  ```C++
  shared_ptr<T> p(q) // p是shared_ptr q的拷贝：递增q的计数器。q中的指针必须能转换为T*。
  p = q // 相互转换，递减p的引用计数，递增q的引用计数。
  p.unique() // 若p的use_count为1，则返回true；否则返回false
  p.use_count() // 返回与p共享对象的智能指针数量；主要用于调试，很慢
  ```

- 使用动态内存的一个常见原因是允许多个对象共享相同的状态。

- 直接管理内存

  ```C++
  // 默认初始化
  int *pi = new int; // pi指向一个动态分配的、未初始化的无名对象。
  string *ps = new string; // 初始化为空string
  
  // 直接初始化
  int *pi = new int(1024);
  string *ps = new string(10, '9');
  vector<int> *pv = new vector<int>{0,1,2,3,4,5,6,7,8,9};
  
  // 值初始化
  string *ps1 = new string(); // 值初始化为空string
  int *pi1 = new int(); // 值初始化为0
  ```

- 内存泄漏

  **memory leak**是指**程序在申请内存后，无法释放已申请的内存空间**（例：比如new操作符创建的对象，未使用delete释放），一次内存泄露危害可以忽略，但内存泄露堆积后果很严重，无论多少内存，迟早会被占光。最终会导致out of memory。

- 空悬指针

  在delete之后，指针就变成了空悬指针。（例：或是局部作用域的指针？出了作用域内存已被释放了）

  ```C++
  int *p(new int(42)); // p指向动态内存
  auto q = p; // q和p指向相同的内存
  delete p; // p和q均变为无效
  p = nullptr; // 指出p不再绑定到任何对象
  // !!!q依然是空悬指针
  ```

- shared_ptr和new结合使用

  ```C++
  shared_ptr<int> p(new int(42)); // p指向一个值为42的int
  shared_ptr<int> p1 = new int(1024); // 错误：隐式不可以（不能用普通的指针去构造一个智能指针），必须使用直接初始化方式
  shared_ptr<int> p2(new int(1024)); // 正确：使用了直接初始化方式
  ```

  **智能指针的构造函数是显式调用的explicit。**

- 默认情况下，用来初始化智能指针的普通指针，必须指向动态内存，否则必须提供操作符来代替delete。

- 定义和改变shared_ptr的其他方法

  ```C++
  shared_ptr<T> p(q) // p管理内置指针的q所指向的对象；q必须指向new分配的内存，且能够转换为T*类型
  shared_ptr<T> p(u) // p从unique_ptr u那里接管了对象的所有权；将u置为空
  shared_ptr<T> p(q, d) // p接管了内置指针q所指向的对象的所有权。q必须能转换为T*类型。p将使用可调用对象d来代替delete
  shared_ptr<T> p(p2, d) // p是shared_ptr p2的拷贝，唯一的区别是p将用可调用对象d来代替delete
  p.reset()
  p.reset(q)
  p.reset(q, d)
  // 若p是唯一指向器对象的shared_ptr，reset会释放此对象，若传递了可选的参数内置指针，会令p指向q，否则会将p置为空。若还传递了参数d，将会调用d而不是delete来释放q
  ```

- 内置指针和智能指针混用的风险

  ```C++
  void process(shared_ptr<int> ptr)
  {
      // 使用ptr
  }// ptr离开作用域，被销毁
  shared_ptr<int> p(new int(42)); // 引用计数为1
  process(p); // 拷贝p会递增它的引用计数；在process中引用计数为2
  int i = *p; // 引用计数为1
  
  // !!!用内置指针显式构造以一个shared_ptr，这样做很可能会导致错误。
  int *x(new int(1024)); 	// 危险：x是一个普通指针
  process(x);				// 错误：不能将int*转换为shared_ptr<int>
  process(shared_ptr<int>(x)); // 合法的，但内存会被释放！
  int j = *x; 				 // 未定义的：x是一个空悬指针！
  ```

- get：向不能使用智能指针的代码，传递一个内置指针。

  **永远不要用get初始化另一个智能指针或为另一个智能指针赋值。**

  ```C++
  shared_ptr<int> p(new int(42)); // 引用计数为1
  int *q = p.get(); // 正确：但使用q时要注意，不要让它管理的指针被释放！
  { // 新程序块
      // 未定义：两个独立的shared_ptr指向相同的内存
      shared_ptr<int> p2(q);
  } // 程序块结束，p2被销毁，它指向的内存被释放
  int foo = *p；// 未定义：p指向的内存已经被释放了
  
  // note：p2->42<-p；p2指向42（计数为1），p也指向42（计数为1），但p和p2彼此不知道对方的存在。 
  ```

- reset：更新引用计数，如果需要的话，会释放p指向的对象。

  ```C++
  p = new int(1024); // 错误：不能将一个普通指针赋予shared_ptr
  p.reset(new int(1024)); // 正确：p指向一个新对象(放弃原有指向的对象)
  
  if(!p.unique())
  {
      p.reset(new string(*p)); // 我们不是唯一用户；分配新的拷贝
  } 
  *p += newVal; // 现在我们知道自己是唯一的用户，可以改变对象的值
  ```

- 如果使用智能指针，即使程序块过早结束，也能正确释放内存

  ```C++
  void f()
  {
      shared_ptr<int> sp(new int(42)); // 分配一个新对象
      // 在这段代码抛出一个异常，且在f中未被捕获
  } // 在函数结束时shared_ptr自动释放内存
  
  // 直接管理内存，则不会
  void f()
  {
      int *p = new int(42); // 动态分配一个对象
      // 这段代码抛出一个异常，且在f中未被捕获
      delete ip; // 在退出之前释放内存（若前面发生了异常，该段代码不会执行到）
  }
  ```

- 使用类似的技术来管理不具有良好定义析构函数的类

  ```C++
  struct destination; // 表示我们正在连接什么
  struct connection;  // 使用连接所需的信息
  connection connect(destionation *); // 打开连接
  void disconnect(connection); // 关闭给定的连接
  void f(destination &d/*其他参数*/)
  {
      // 获得一个连接：记住使用完后要关闭它
      connection c = connect(&d);
      // 使用连接
      // 如果我们在f退出前忘记调用disconnect，就无法关闭
  }
  
  // 使用我们自己的释放操作！
  void end_connection(connection *p)
  {
      disconnect(*p);
  }
  
  void f(destination &d/*其他参数*/)
  {
      // 获得一个连接：记住使用完后要关闭它
      connection c = connect(&d);
      shared_ptr<connection> p(&c, end_connection); // end_connection相当于deleter
      // 使用连接
      // 当f退出时（即使是由于异常而退出），connection会被正确关闭
  }
  ```

#### 12.1.2 unique_ptr

- **unique_ptr不支持拷贝和赋值**

  ```C++
  unique_ptr<int> p2(p1); // 错误：不支持拷贝
  unique_ptr<int> p3;
  p3 = p2; // 错误：不支持赋值
  ```

- unique_ptr的操作

  ```C++
  unique_ptr<T> u1;
  unique_ptr<T, D> u2;
  unique_ptr<T, D> u(d); // 空unique_ptr，指向类型为T的对象，用类型为D的对象d代替delete
  u = nullptr; // 释放u指向的对象，将u置为空
  u.release(); // u放弃对指针的控制权，返回指针（把控制权返回了），并将u置为空
  u.reset();   // 释放u指向的对象
  u.reset(q);  // 如果提供了内置指针q，令u指向这个对象；否则将u置为空
  u.reset(nullptr); 
  ```

- unique_ptr不支持拷贝和赋值，**但可以通过release或reset将指针的所有权从一个（非const）的转义给另一个**

  ```C++
  unique_ptr<string> p2(p1.release()); // release将p1置为空
  unique_ptr<string> p3(new string("Trex"));
  // 将所有权从p3转移给p2
  p2.reset(p3.release()); // reset释放了p2原来指向的内存（p2指向了p3原来指向的内存）
  p2.release(); // 内存泄漏（p2松手后，没有人接手p2指向的内存）
  auto p = p2.release(); // OK, 记住要delete p
  
  // 不能拷贝的例外：可以拷贝或赋值一个将要被销毁的unique_ptr
  unique_ptr<int> clone(int p)
  {
      // 正确：从int* 创建一个unique_ptr<int>
      return unique_ptr<int>(new int(p)); // "临时对象生命周期要结束了，控制权交给返回值"
  }
  
  unique_ptr<int> clone(int p)
  {
      unique_ptr<int> ret(new int(p)); // 局部对象
      // ...
      return ret; // 正确：返回的是即将销毁的局部对象
  }
  ```

- 向unique_ptr传递删除器

  ```C++
  void f(destination &d/*其他参数*/)
  {
      connection c = connect(&d); // 打开连线
      // 但p被销毁时，连接将会关闭
      unique_ptr<connection, decltype(end_connection)*> p(&c, end_connection);
      // 使用连接
      // 当f退出时（即使是由于异常而退出），connection会被正确关闭
  }
  ```

#### 12.1.3 weak_ptr

- weak_ptr绑定到shared_ptr，不会改变引用计数。

- weak_ptr的操作

  ```C++
  weak_ptr<T> w // 空weak_ptr可以指向类型为T的对象
  weak_ptr<T> w(sp) // 与shared_ptr sp指向相同对象的weak_ptr。T必须能转换为sp指向的类型
  w = p // p可以是一个shared_ptr或一个weak_ptr。赋值后w与p共享对象
  w.reset() // 将w置为空
  w.use_count() // 与w共享对象的shared_ptr的数量
  w.expired() // 若w.use_count()为0，返回true（"过期了"） ，否则返回false 
  w.lock() // 如果expired为true，返回一个空shared_ptr；否则返回一个指向w的对象的shared_ptr
      
  auto p = make_shared_ptr<int>(42);
  weak_ptr<int> wp(p); // wp弱共享p；p的引用计数未改变
  // 不能使用weak_ptr直接访问对象，必须调用lock
  if (shared_ptr<int> np = wp.lock()) // 如果np不为空则条件成立
  {
      ...
  }
  ```


### 12.2 动态数组

- new和数组

  动态数组不是数组类型，分配动态数组会得到一个元素类型的指针。

  ```C++
  // 调用get_size确定分配了多少个int
  int *pia = new int[get_size()]; // pia指向第一个int
  // 方括号中的大小必须是整数，但不必是常量
  
  typedef int arrT[42]; // arrT表示42个int的数组类型
  int *p = new arrT; // 编译器会执行: int *p = new int[42]
  ```

- 初始化动态分配对象的数组

  ```C++
  int *pia3 = new int[10]{0,1,2,3,4,5,6,7,8,9};
  ```

- 动态分配一个空数组是合法的，内置数组不行

- 释放动态数组：delete[] pa;

- 智能指针和动态数组

  ```C++
  unique_ptr<int[]> up(new int[10]); // up指向一个包含10个未初始化int的数组
  up.release(); // 自动用delete[]销毁其管理的指针
  // up不支持成员访问运算符!
  for(size_t i = 0; i != 10; ++i)
      up[i] = i;
  ```

  shared_ptr不直接支持管理动态数组。需要自定义删除器。

- allocator类：将内存分配和对象构造分离

  分配大块内存，但只在真正需要时才指向指向对象创建操作。

  ```C++
  // 将内存分配和对象构造组合在一起可能导致不必要的浪费
  string *const p = new string[n]; // 构造n个空string
  string s;
  string *q = p; // q指向第一个string
  while(cin >> s && q != p+n)
      *q++ = s; // 赋予*q一个新值
  const size_t size = q - p; // 记住我们读取了多少个string
  // 使用数组
  delete []p; // p指向一个数组，记得用delete[]来释放
  ```

  上面代码的问题：

  1）我们可能不需要n个string；

  2）每个对象都赋予了两遍值；

  3）没有默认构造函数的类就不能动态分配数组了。

  | 操作                   | 解释                                                         |
  | ---------------------- | ------------------------------------------------------------ |
  | `allocator<T> a`       | 定义了一个名为`a`的`allocator`对象，它可以为类型为`T`的对象分配内存 |
  | `a.allocate(n)`        | 分配一段原始的、未构造的内存，保存`n`个类型为`T`的对象。     |
  | `a.deallocate(p, n)`   | 释放从`T*`指针`p`中地址开始的内存，这块内存保存了`n`个类型为`T`的对象；`p`必须是一个先前由`allocate`返回的指针。且`n`必须是`p`创建时所要求的大小。在调用`deallocate`之前，用户必须对每个在这块内存中创建的对象调用`destroy`。 |
  | `a.construct(p, args)` | `p`必须是一个类型是`T*`的指针，指向一块原始内存；`args`被传递给类型为`T`的构造函数，用来在`p`指向的内存中构造一个对象。 |
  | `a.destroy(p)`         | `p`为`T*`类型的指针，此算法对`p`指向的对象执行析构函数。     |

  ```C++
  allocator<string> alloc; // 可以分配string的allocator对象
  auto const p = alloc.allocate(n); // 分配n个未初始化的string
  
  auto q = p; // q指向最后构造的元素之后的位置
  alloc.construct(q++); // *q为空字符串
  alloc.construct(q++,10,'c'); // *q为cccccccccc
  alloc.construct(q++,"hi"); // *q为hi
  
  cout << *p << endl; // 正确
  cout << *q << endl; // 错误，q指向未构造的内存
  
  while(q!=p)
      alloc.destroy(--q); // 释放我们正在构造的string, 我们只能对正在构造了的元素进行destroy操作
  alloc.deallocated(p,n); // 释放内存
  
  // q有点类似尾后指针 end()
  ```

- 标准库为allocator类定义了两个伴随算法，可以在未初始化内存中创建对象。
