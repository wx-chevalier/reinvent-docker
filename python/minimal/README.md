# focker.py

一个模拟 Docker 的 container 系统

```s
mkdir /tmp/rootfs && tar -Jxf centos-7-docker.tar.xz -C /tmp/rootfs && git clone https://github.com/fireflyc/mini-docker.git
cd mini-docker/ && pipenv shell && python setup.py develop
```
