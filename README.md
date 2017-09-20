# vuepack
Modern Template For vue-cli, with  Vue.js, Webpack 3, Vue-Router, Vuex, MobX, etc.

本模板收到了 [egoist/vuepack](https://github.com/egoist/vuepack) 的启发，是对于笔者的 [create-webpack-app/vue](https://github.com/wxyyxc1992/create-webpack-app/tree/master/vue) 的模板化改造。

# 常见问题

## 离线模板

将对应的模板下载到：~/.vue-templates 目录下，然后初始化的时候选择：

```s
$ vue init -offline test webpack
```

即可以优先使用本地缓存的模板。

## SSL 校验

vuepack 默认使用 Nightwatch 进行 E2E 测试，其在安装的时候会自动使用 Git 下载 phantomjs；我们可以手动从[这里](https://github.com/Medium/phantomjs/releases/download/v2.1.1/phantomjs-2.1.1-windows.zip)下载 phantomjs 安装包并且添加到系统环境变量路径中。

```s
Error making request.
Error: unable to verify the first certificate
    at TLSSocket.<anonymous> (_tls_wrap.js:1108:38)
    at emitNone (events.js:105:13)
    at TLSSocket.emit (events.js:207:7)
    at TLSSocket._finishInit (_tls_wrap.js:638:8)
    at TLSWrap.ssl.onhandshakedone (_tls_wrap.js:468:38)
```

# About

## Roadmap
