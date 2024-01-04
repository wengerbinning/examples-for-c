

## npm

###  项目开发


#### 准备环境

```shell
npm init
```


```shell
# npm config set registry https://mirrors.huaweicloud.com/repository/npm/

npm install --save-dev electron
```

#### 开发调试

```
npm run start
```

### 发布版本

#### 准备环境

```shell
npm install --save-dev @electron-forge/cli
```

```shell
npx electron-forge import
```