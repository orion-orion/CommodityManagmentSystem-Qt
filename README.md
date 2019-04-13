# 《京东物流管理系统》    
## 概述  
该管理系统用C++语言结合Qt的GUI框架开发，并支持数据库的使用。因为试验环境是单机，不需要连接远程服务器，故这里的数据库是用小型轻量型的SQLite。当然，我在源代码中留有其他数据库的接口，如果有需求，也可以添加其他数据库的连接。因为时间紧迫，加之作者本人水平有限，目前该系统尚不支持Oracle。MySQL等企业级的大型数据库系统，日后会在项目中逐渐完善此功能，欢迎您加入我的项目中，与我一同完善这个项目。  
## 功能简介  
该系统用于管理仓库中的货物ID编号，名称，库存数量，保质期等信息，并提供搜索货物，添加货物和删除货物信息的功能。除此之外，仓库里的货物信息会按照货物的ID大小进行自动排序，十分方便。使用数据库对信息进行存储，安全高效。  
该产品的功能概括如下：  
- [x] 对货物的ID编号，名称，库存数量，保质期进行储存    
- [x] 用数据库进行储存  
- [x] 货物的信息在数据库中按ID顺序自动排列   
- [x] 按照分类或货物名臣搜索货物的信息功能支持   
- [x] 货物信息提供增加，删除和查找等功能支持   
- [x] 管理员登录口令设置  
- [ ] 支持Oracle。MySQL等企业级的数据库系统  
- [ ] 数据库验证码防SQL注入功能。  
## 界面简介   
### 1.数据库连接界面。  
目前暂时只提供SQLlite数据库支持。后续功能正在开发之中。  
![数据库连接界面](/ScreenShoot/%E6%95%B0%E6%8D%AE%E5%BA%93%E8%BF%9E%E6%8E%A5%E7%95%8C%E9%9D%A2.png)  
2.登录界面  
为管理员设置了口令，初始用户名为admin，密码为12345，只有输入正确口令才能登陆。  
![登录界面](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E7%99%BB%E5%BD%95%E7%95%8C%E9%9D%A2.png)  
如果口令输入错误，会弹出以下界面：    
![密码错误警告](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E5%AF%86%E7%A0%81%E9%94%99%E8%AF%AF%E8%AD%A6%E5%91%8A%E7%AA%97%E5%8F%A3.png)    
3.主窗口界面。左边分区显示货物信息。右上部分分区为滑动动态信息显示区。右下部分为操作菜单。提供删除、添加、查找、退出系统等多种操作。  
![主窗口界面](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E4%B8%BB%E7%AA%97%E5%8F%A3%E7%95%8C%E9%9D%A2.png)  
4.产品信息区域。    
产品信息区域为一个数据表，包括了产品的ID编号，分类，名称，产地，品质，保质期等信息。生成的表格自动按照ID的递增排序，方便管理和查看。  
![产品信息区域] (https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E4%BA%A7%E5%93%81%E4%BF%A1%E6%81%AF%E5%8C%BA%E5%9F%9F.png)    
5.滑动信息显示区。    
当鼠标移动到某一个产品那一栏时，该滑动信息显示区会显示出相应的产品信息细节。  
![滑动信息显示区](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E4%BA%A7%E5%93%81%E7%BB%86%E8%8A%82%E5%8C%BA%E5%9F%9F%EF%BC%88%E5%8A%A8%E6%80%81%EF%BC%89.png)    
6.操作菜单。  
![操作菜单] (https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E6%93%8D%E4%BD%9C%E8%8F%9C%E5%8D%95.png)  
7.添加信息窗口。  
![添加信息窗口](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E6%B7%BB%E5%8A%A0%E4%BF%A1%E6%81%AF%E7%AA%97%E5%8F%A3.png)    
8.查找信息：按类别模糊搜索  
![按类别搜索](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E6%8C%89%E7%B1%BB%E5%88%AB%E6%90%9C%E7%B4%A2.png)  
按类别搜索结果：  
![按类别搜索结果](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E6%8C%89%E7%B1%BB%E5%88%AB%E6%90%9C%E7%B4%A2%E7%BB%93%E6%9E%9C.png)    
9.查找信息：名称明确搜索  
![按名称搜索](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E6%8C%89%E5%90%8D%E5%AD%97%E6%90%9C%E7%B4%A2.png)    
按名称搜索结果：    
![按名称搜索结果](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E6%8C%89%E5%90%8D%E5%AD%97%E6%90%9C%E7%B4%A2%E7%BB%93%E6%9E%9C.png)  
10.删除信息操作  
![删除信息操作](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E5%88%A0%E9%99%A4%E4%BF%A1%E6%81%AF%E6%93%8D%E4%BD%9C.png)  
删除信息操作确认  
![删除信息确认窗口](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E5%88%A0%E9%99%A4%E7%A1%AE%E8%AE%A4%E7%AA%97%E5%8F%A3.png)  
11.滑动显示区演示  
![滑动显示区演示](https://github.com/lonelyprince7/CommodityManagmentSystem-Qt/blob/master/ScreenShoot/%E6%BB%91%E5%8A%A8%E4%BF%A1%E6%81%AF%E6%BC%94%E7%A4%BA.png)  
