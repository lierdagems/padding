# 说明

这是一个用于制作1k的0字节填充的程序，在制作sd卡烧写nand的镜像时，需要将编
译好的u-boot.imx进行1k的0字节填充

编译
====

```shell
./configure
make
```

使用
====

```shell
./padding u-boot.imx
```

将生成的u-boot-padding.imx拷贝到sd卡中
