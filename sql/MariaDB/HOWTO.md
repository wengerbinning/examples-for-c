
```shell
mariadb-install-db --user=mysql --basedir=/usr --datadir=/db/mariadb
```

```shell
mariadb-secure-installation
```


```shell
#
# sudo mysqld_safe --skip-grant-tables --skip-networking &

#
sudo mariadbd-safe --skip-networking &
```

```mariadb
ALTER USER 'root'@'localhost' IDENTIFIED BY 'root';
```

```mariadb
CREATE USER 'wenger'@'localhost' IDENTIFIED BY '@wengerbinning';

GRANT ALL PRIVILEGES ON database.* TO 'wenger'@'localhost';

GRANT ALL PRIVILEGES ON *.* TO 'wenger'@'localhost';

FLUSH PRIVILEGES;
```

```shell
mariadb -u root -p
```


#### 默认数据库

* information_schema

* performance_schema
* sys
* test
* mysql - 用于管理用户