#include <stdio.h>
// #include <stddef.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

// 说明：获得结构体(TYPE)的变量成员(MEMBER)在此结构体中的偏移量。
// (01)  ( (TYPE *)0 )   将零转型为TYPE类型指针，即TYPE类型的指针的地址是0。
// (02)  ((TYPE *)0)->MEMBER     访问结构中的数据成员。
// (03)  &( ( (TYPE *)0 )->MEMBER )     取出数据成员的地址。由于TYPE的地址是0，这里获取到的地址就是相对MEMBER在TYPE中的偏移。
// (04)  (size_t)(&(((TYPE*)0)->MEMBER))     结果转换类型。对于32位系统而言，size_t是unsigned int类型；对于64位系统而言，size_t是unsigned long类型。

struct Student
{
    char gender;
    int id;
    int age;
    char name[20];
};

// 说明：简单说说"为什么id的偏移值是4，而不是1"。
// 我的运行环境是linux系统，32位的x86架构。这就
// 意味着cpu的数据总线宽度为32，每次能够读取4字
// 节数据。gcc对代码进行处理的时候，是按照4字节
// 对齐的。所以，即使gender是char(一个字节)类型，
// 但是它仍然是4字节对齐的！

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

#define container_of(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

// 说明：根据"结构体(type)变量"中的"域成员变量(member)的指针(ptr)"来获取指向整个结构体变量的指针。
// (01) typeof( ( (type *)0)->member )     取出member成员的变量类型。
// (02) const typeof( ((type *)0)->member ) *__mptr = (ptr)    定义变量__mptr指针，并将ptr赋值给__mptr。
//      经过这一步，__mptr为member数据类型的常量指针，其指向ptr所指向的地址。
// (04) (char *)__mptr    将__mptr转换为字节型指针。
// (05) offsetof(type,member))    就是获取"member成员"在"结构体type"中的位置偏移。
// (06) (char *)__mptr - offsetof(type,member))    就是用来获取"结构体type"的指针的起始地址（为char *型指针）。
// (07) (type *)( (char *)__mptr - offsetof(type,member) )    就是将"char *类型的结构体type的指针"转换为"type *类型的结构体type的指针"。

int main(int argc, char const *argv[])
{
    int gender_offset, id_offset, age_offset, name_offset;

    gender_offset = offsetof(struct Student, gender);
    id_offset = offsetof(struct Student, id);
    age_offset = offsetof(struct Student, age);
    name_offset = offsetof(struct Student, name);
    
    printf("gender_offset = %d\n", gender_offset);
    printf("id_offset = %d\n", id_offset);
    printf("age_offset = %d\n", age_offset);
    printf("name_offset = %d\n", name_offset);

    printf("sizeof(struct Student) = %d\n", sizeof(struct Student));
    // ----------------------------------------------------------------------------------------------------------------
    
    struct Student stu;
    struct Student *pstu;

    stu.gender = '1';
    stu.id = 9527;
    stu.age = 24;
    strcpy(stu.name, "zhiwen");

    // 根据"id地址" 获取 "结构体的地址"。
    pstu = container_of(&stu.id, struct Student, id);

    // 根据获取到的结构体student的地址，访问其它成员
    printf("gender= %c\n", pstu->gender);
    printf("age= %d\n", pstu->age);
    printf("name= %s\n", pstu->name);

    return 0;
}