> :information_source: This project is currently work in progress

# lrn-gen

**lrn-gen**, a generator for projects using **lrn**.

---
### Dependencies
In order to make it work you need to link
[chr](https://github.com/ChronesIO/chr),
[fmt](https://github.com/fmtlib/fmt)
and
[pugixml](https://github.com/zeux/pugixml)
to it. \
You can do that using
[vcpkg](https://github.com/microsoft/vcpkg):
```cmake
target_link_libraries(lrn-gen PRIVATE chr)
target_link_libraries(lrn-gen PRIVATE chr-math)

find_package(pugixml CONFIG REQUIRED)
target_link_libraries(lrn-gen PRIVATE pugixml pugixml::static pugixml::pugixml)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(lrn-gen PRIVATE fmt::fmt)
```
Visit our guide *here (coming soon)* on how to link ChronesIO projects into your project.

---
### Functionality
**lrn-gen** converts your Xml UI files into C++ header and implementation files
*(at least it will soon)*.

*(future) Example:*
```xml
<page obj="My::Name::Space::MyPage">
    <vstack>
        <button name="MyButton1" text="Hello1" clicked="*"/>
        <button name="MyButton2" text="Hello2" clicked="IWasClicked"/>
        <button name="MyButton3" text="Hello3" clicked="Function::Somewhere"/>
        <hstack>
            <text text="In the same "/>
            <text text="line"/>
        </hstack>
        <view page="My::Other::Page4"/>
    </vstack>
</page>
```
This then can be used in the element class *(experimental)*:
```c++
namespace My::Name::Space
{
    struct MyPage
    {
        LRN_GEN_IMPL__MyPage
        
        // clicked="*" -> clicked="MyButton1_Clicked"
        void MyButton1_Clicked(ButtonClickedEventArgsRef e)
        {
            cout << "MyButton1 clicked!" << endl;
            MyButton2.Disable();
        }
        
        void IWasClicked(ButtonClickedEventArgsRef e)
        {
            cout << "I WAS CLICKED!" << endl;
            MyButton3.Enable();
        }
    };
}

void Function::Somewhere(MyPage* self, ButtonClickedEventArgsRef e)
{
    cout << "Somewhere far away..." << endl;
    self->MyButton2.Enable();
    self->MyButton3.Disable();
}
```