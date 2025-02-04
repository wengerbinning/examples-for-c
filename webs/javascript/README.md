

DOM(Document Object Model, 文档对象模型)



#### 嵌入HTML

当javascript嵌入HTML中可以放在head或body中， 一般放在head或body末尾; 并使用script标签标识。

```html
<script>
function sum() {
    // TODO
}
</script>
```

#### 脚本文件

```js
// file: funcs.js
function func() {
    // TODO
}
```


```html
<script src="funcs.js"></script>
```

```js
document.getElementById("demo").innerHTML = "";
```

```js
alert("pop message");
```