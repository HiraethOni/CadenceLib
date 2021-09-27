# CadenceLibQML

> 使用QML编写的OrCAD封装数据库管理工具

## 构建

**Windows** :![BuildStatus](https://github.com/HiraethOni/CadenceLib/workflows/Build/badge.svg)

## Feature

- [x] 数据新增
- [ ] 数据编辑
- [ ] 数据删除
- [ ] 数据批量删除

## Usage

* 将Cadence配置成用`Mysql`引擎管理，[可参考此教程](https://blog.csdn.net/weixin_43908559/article/details/95490195)
* 下载发布版本，并且按照配置文档说明填写配置文档
* 启动软件，新增数据信息

## Config

本软件采用`config.ini`进行配置管理，在没有此文件时软件会自动生成一个默认的配置文件

```ini
[mariadb]
host=localhost
username=username
passwd=passwd
port=3306
database_name=databaseName
[language]
language=zh_CN
[Allegro Footprints]
path=X:\\ProgramData\\Cadence\\Cadence_Lib\\Library\\Package
```

* 其中，[mariadb]字段内为数据库基本信息配置，这里特别注意一点：在`Windows`下，`database_name`为你在`系统DSN`设置的名字
* `Allegro Footprints`这个字段用来扫描所有的PCB封装方便添加