### 介绍
该库为轻量级的c++ json解析与构造库，源码很短，适合学习，觉得ok的点个star吧。

提供了的功能：

- json字符串解析为c++对象（JSONArray和JSONObject）
- c++对象中获取key-value值
- c++对象转化为json字符串

除此之外，由于json支持了多种数据类型，还可以将JSONArray对象看成是python的list，JSONObject看成是python的dict，库中提供了方便操作的api函数。例如以下初始化方法，

```cpp
JSONArray arr = {123.4, "dfsdf", 23, nullptr}; // 类似于python的list
JSONArray arr2 = LIST(1.23, "sdfsdg", 234, nullptr); //提供一个LIST初始化宏，类似于python的list
JSONObject obj = {
    {"test obj", {"key", "value"}},
    {"int number", 2},
    {"float number", 34.3},
    {"my string", "fsdfsdg"},
    {"nullptr", nullptr},
    {"emptylist", {}},
}; // 可以看成是python的dict
JSONObject obj2 = OBJECT(
            KEYVALUE("username", "hhk"),
            KEYVALUE("obj", OBJECT(
                    KEYVALUE("abcd", LIST(1,2.3, "hahahaha")),
                    KEYVALUE("obj", OBJECT(
                            KEYVALUE("key", "this is obj.obj.key' s value")
                    ))
            )),
            KEYVALUE("null", nullptr),
            KEYVALUE("list", LIST(1, "qwerty", 2.34, OBJECT(
                            KEYVALUE("key", "this is a key"),
                            KEYVALUE("key2", "this is a key2"),
                    ))),
    		);  // 提供了一个初始化宏，类似于python的dict
// 注：使用OBJECT LIST初始化宏的目的是为了替代{}来进行初始化，因为有时候大括号看起来会不够直观。
```

实现该库的一些技巧：

- 参考boost any.hpp ，实现一个可以在容器里容纳任意类型的对象

- typeid 进行类型的判断

- 使用了很多递归方法

  

### 编译
编译依赖：
- cmake
- gcc

如果是windows平台可以使用MinGW或Cygwin或msys64的gcc来编译，配合clion，开发起来挺方便的。

例如windows平台下（linux下类似），编译静态库的方法如下，编译成功后在build目录下生成libejson.a静态库和ejson_test.exe可执行文件(linux下平台生成的可执行文件没有.exe)。

![](./pic/pic1.jpg)

运行测试程序：

![1553961192371](./pic/1553961192371.png)

手动编译测试程序方法如下：(-lejson参数表示链接libejson.a静态库， -I参数为增加include的搜索目录)

![](./pic/pic2.jpg)



### 提供方便的API

这里Json支持的类型有int, float, double, const char* , string,  nullptr(cpp中的空指针)

1. **JSON Array**

   - 使用 [] 操作符写入数据，可以使用cout直接打印输出

     ```cpp
     JSONArray test1(2); // 初始化分配大小，可以会自动拓展容量
     test1[0] = nullptr;
     test1[1] = "this is const char*";
     test1[2] = 12324.5;
     test1[5] = "中文字符串";
     cout << test1 << endl;
     ```

   - 初始化列表构造函数与链式操作

     ```cpp
     JSONArray arr = {123.4, "dfsdf", 23, nullptr}; // 初始化列表 
     arr[0] = 12.314;
     arr[2] = 2335;
     arr[3] = "字符串";
     arr[6] = obj;  // json对象
     arr.add(123456) // 整数
        .add(234.235236) //浮点数
        .add("字符串") //字符串
        .add(nullptr); // null测试
     ```

   - get方法获取数值

     例如 `float f = test1.get<float>(2);`  ，如果类型不正确的话会抛出异常

   - toString方法转换为字符串，toString可选参数，代表缩进的数量。

     例如 `test1.toString(4)` 表示4空格缩进
2. **JSON Object**

   - 使用 [] 来写入数据

     ```cpp
     // 使用[] 操作对象
     JSONObject test2;
     test2["float"] = 123.456;
     test2["int"] = 24;
     test2["string"] = "this is a string";
     test2["array"] = test1;
     test2["nullptr"] = nullptr;
     cout << test2 << endl;
     ```

   - 更加复杂的初始化方法

     这种方法看起来比较直观，支持object和array的嵌套使用，这是我自己想出来的，有兴趣的朋友可以看下我的实现方法，讨论下有没有更加优秀的实现方式。

     ```cpp
     // obj初始化方法
     JSONObject obj = {
         {"test obj", {"key", "value"}},
         {"int number", 2},
         {"float number", 34.3},
         {"my string", "fsdfsdg"},
         {"nullptr", nullptr},
         {"emptylist", {}},
         {"列表嵌套列表", {1,2.3, "sdf", {1,2.242, "float"}}}, // 列表嵌套
         {"列表嵌套对象和列表", {
             {{"key1", 1234}}, // 被认为是对象
             {"key1", 1234}, // 被认为是列表
             1.23,
             234325
         }},
         {"对象", { // 所有的值都是{key, value}对则认为是嵌套对象
             {"a obj", 1234566},
             {"b obj", "b obj value"},
         }}
     };
     ```
     这种方法有时候还是有点不够直观，所以我弄了一个宏，使得编写json时更加直观

     ```cpp
     JSONObject context = OBJECT(
                 KEYVALUE("username", "hhk"),
                 KEYVALUE("obj", OBJECT(
                         KEYVALUE("abcd", LIST(1,2.3, "hahahaha")),
                         KEYVALUE("obj", OBJECT(
                                 KEYVALUE("key", "this is obj.obj.key' s value")
                         ))
                 )),
                 KEYVALUE("null", nullptr),
                 KEYVALUE("list", LIST(1, "qwerty", 2.34, OBJECT(
                                 KEYVALUE("key", "this is a key"),
                                 KEYVALUE("key2", "this is a key2"),
                         ))),
                 KEYVALUE("list1", LIST(1,2,3,4,5)),
                 KEYVALUE("list2", LIST(1,2,3)),
                 KEYVALUE("obj2", OBJECT(
                         KEYVALUE("key1", "value1"),
                         KEYVALUE("key2", 222),
                         KEYVALUE("key3", 333),
                 )),
                 KEYVALUE("a", "111"),
                 KEYVALUE("b", "222"),
                 KEYVALUE("c", "333"),
         );
     ```

     这里有三个宏，分别是OBJECT，KEYVALUE， LIST。

   - 支持链式add的操作

     ```cpp
     obj["int"] = 12325;
     obj["float"] = 24235.235235;
     obj["string"] = "this is a string2";
     obj["null"] = nullptr;
     
     obj.add("int", 123) // 整数
         .add("float", 23.2324) // 浮点数
         .add("string", "this is a string") // 英文字符串
         .add("中文", "这是中文字符串。。。") // 中文字符串
         .add("symbols  \",.[]@!#$%^", "含有特殊符号\"") // 特殊符号
         .add("list", {1, 2.34, "english string", 123.4, "中文字符串"}) // 列表
         .add("this is null", nullptr) // null测试
         .add("object", {{"key1", "value1"}, {"key2", 223}, {"key3", 23.4}}); // 对象
     ```

   - get 方法获取数值

     例如， ` obj->get<string>("string")` 可以获取到键为string的值。

   - toString方法输出字符串，参数为缩进的数量

     例如4空格缩进如下(`obj.toString(4)`)

     ![1551941891253](./pic/pic3.png)

     

     无缩进（`obj.toString(-1)`）

     ![1551942038488](./pic/pic4.png)

     无空格缩进(` obj.toString(0)`)

     ![1551942154905](./pic/pic5.png)

3. **字符串转换为json对象**

   由于我们不知道字符串是array还是object，我们使用JSONBase类来接受返回的结果。

   （JSONBase中有isJSONArray 和 isJSONArray 方法，可以方便我们进行类型判断）

   例如以下,

   ```cpp
   string parse_str = R"({"name" : "hhk" , "key1": "valu\"e1 ","key2":[1,2,"asd",{"sadf": 123, "sb": 12.3}, 123.3]})";
   JSONBase* a = JSONBase::parse(parse_str);
   cout << *a << endl;
   JSONObject *b = dynamic_cast<JSONObject *>(a); //类型转换
   cout << b->get<string>("key1") << endl;
   cout << b->get<JSONArray>("key2").get<int>(1) << endl;
   ```

   parse方法用于不知道字符串是array还是object，parse_obj方法返回JSONObject，parse_arr方法返回JSONArray。（parse_obj,parse_arr用于明确知道字符串的类型）

   如果字符串不是json字符串，则抛出JSONParseException异常。

   

   
