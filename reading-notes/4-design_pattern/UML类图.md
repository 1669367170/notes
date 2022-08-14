- [ UML类图](#head1)
	- [ 1、泛化关系](#head2)
	- [ 2、实现关系](#head3)
	- [ 3、关联关系](#head4)
	- [ 4、聚合关系](#head5)
	- [ 5、组合关系](#head6)
	- [ 6、依赖关系](#head7)
	- [ 7、小结](#head8)
	- [ 参考链接](#head9)
# <span id="head1"> UML类图</span>

![30分钟学会UML类图](https://pic1.zhimg.com/v2-941a070601f399d992125ef31261637e_1440w.jpg?source=172ae18b)

> - 在UML类图中，常见的有以下几种关系：**泛化**（Generalization）, **实现**（Realization），**组合**(Composition)，**聚合**（Aggregation），**关联**（Association)，**依赖**(Dependency)。
>
> - 在UML类图中矩形框表示一个类，类分三层，**第一层是；类的名称，如果是抽象类，则用斜体显示，第二层表示特性，是字段和属性，第三层表示操作，通常是方法和行为**。
> - 注意前面符号，“+”表示public，“-”表示private，“#”表示protected。

## <span id="head2"> 1、泛化关系</span>

> **是一种继承关系，表示一般与特殊的关系，它指定了子类如何具体化父类的所有特征和行为。**例如：老虎是动物的一种，即有老虎的特性也有动物的共性。

![image-20220814102906681](C:\Users\16693\AppData\Roaming\Typora\typora-user-images\image-20220814102906681.png)

## <span id="head3"> 2、实现关系</span>

> **一种类与接口的关系，表示类是接口所有特征和行为的实现。**

![image-20220814103513005](C:\Users\16693\AppData\Roaming\Typora\typora-user-images\image-20220814103513005.png)

## <span id="head4"> 3、关联关系</span>

> - **是一种拥有的关系，它使一个类知道另一个类的属性和方法；**如：老师与学生，丈夫与妻子关联可以是双向的，也可以是单向的。双向的关联可以有两个箭头或者没有箭头，单向的关联有一个箭头。
> - 代码实现：成员变量。

![image-20220814103727676](C:\Users\16693\AppData\Roaming\Typora\typora-user-images\image-20220814103727676.png)

## <span id="head5"> 4、聚合关系</span>

> - **是整体与部分的关系，且部分可以离开整体而单独存在。**如车和轮胎是整体和部分的关系，轮胎离开车仍然可以存在。**聚合关系是关联关系的一种，是强的关联关系；**关联和聚合在语法上无法区分，必须考察具体的逻辑关系。
> - 代码实现：成员变量。

![image-20220814103904998](C:\Users\16693\AppData\Roaming\Typora\typora-user-images\image-20220814103904998.png)

## <span id="head6"> 5、组合关系</span>

> - **是整体与部分的关系，但部分不能离开整体而单独存在。**如公司和部门是整体和部分的关系，没有公司就不存在部门。**组合关系是关联关系的一种，是比聚合关系还要强的关系，**它要求普通的聚合关系中代表整体的对象负责代表部分的对象的生命周期。
> - 代码实现：成员变量。

![image-20220814104156885](C:\Users\16693\AppData\Roaming\Typora\typora-user-images\image-20220814104156885.png)

## <span id="head7"> 6、依赖关系</span>

> - **是一种使用的关系，即一个类的实现需要另一个类的协助，**所以要尽量不使用双向的互相依赖。
> - 代码实现：局部变量、方法的参数或者对静态方法的调用。

![image-20220814104142851](C:\Users\16693\AppData\Roaming\Typora\typora-user-images\image-20220814104142851.png)

## <span id="head8"> 7、小结</span>

> **各种关系的强弱顺序：泛化 = 实现 > 组合 > 聚合 > 关联 > 依赖。**

下面这个UML图，比较形象地展示了各种类图关联关系：

（注：大雁和雁群之间的聚合关系，菱形标反，应指向雁群。）

![image-20220814105937593](C:\Users\16693\AppData\Roaming\Typora\typora-user-images\image-20220814105937593.png)



## <span id="head9"> 参考链接</span>

https://zhuanlan.zhihu.com/p/35238252