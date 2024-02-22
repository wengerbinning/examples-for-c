
## 数据类型

#### TINYINT
#### SMALLINT
#### MEDIUMINT
#### INT or INTEGER
#### BIGINT
#### FLOAT
#### DOUBLE
#### DECIMAL    

#### DATE
#### TIME
#### YEAR
#### DATATIME
#### TIMESTAMP

#### CHAR
#### VARCHAR
#### TINYBLOB
#### TINYTEXT
#### BLOB
#### TEXT
#### MEDIUMBLOB
#### MEDIUMTEXT
#### LONGBLOB
#### LONGTEXT

#### ENUM
#### SET

#### GEOMETRY
#### POINT
#### LINESTRING
#### POLYGON
#### MULTIPOINT
#### MULTILINESTRING
#### MULTIPOLYGON
#### GEOMETRYCOLLECTION


## 操作说明

```mysql
SHOW DATABASES;
```

```mysql
CREATE DATABASE database;
```

```mysql
CREATE DATABASE IF NOT EXISTS database 
    CHARACTER SET charset
    COLLATE collation;
```

```mysql
DROP DATABASE database; 
```

```mysql
DROP DATABASE IF EXISTS database; 
```

```mysql
USE database;
```


#### 数据表

```mysql
SHOW TABLES;
```

```mysql
CREATE TABLE table (
    col1 type,
    col2 type,
    ...
);
```

AUTO_INCREMENT
PRIMARY KEY
NOT NULL
DEFAULT TRUE

```mysql
DROP TABLE table;
```

```mysql
DROP TABLE IF EXISTS table;
```

```mysql
ALTER TABLE table
    ADD COLUMN col type;
```

```mysql
ALTER TABLE table
    MODIFY COLUMN col type;
```

```mysql
ALTER TABLE table
    CHANGE COLUMN col_old col_new type_new;
```

```mysql
ALTER TABLE table
    DROP COLUMN col;
```

```mysql
ALTER TABLE table
    ADD PRIMARY KEY (col);
```

```mysql
ALTER TABLE table
    RENAME TO table_new;
```

临时表

```mysql
CREATE TEMPORARY TABLE table (
    col1 type,
    col2 type,
);
```

#### 数据项

```mysql
INSERT INTO table (col1, col2, ...) VALUES (val1, val2, ...);
```

```mysql
INSERT INTO table VALUES (val1, val2, ...);
```

```mysql
INSERT INTO table 
    VALUES 
        (val1, val2, ...),
        (val1, val2, ...),
        (val1, val2, ...),
    ;
```

```mysql
SELECT col1, col2, ... FROM table;
```

```mysql
SELECT col1, col2, ... FROM table LIMIT number;
```

```mysql
SELECT col1, col2, ... FROM table WHERE condition;
```

```mysql
SELECT col1, col2, ... FROM table WHERE col LINK pattern;
```

```mysql
SELECT col1, col2, ... FROM table ORDER BY col;
```

```mysql
SELECT col1, col2, ... FROM table
UNION
SELECT col1, col2, ... FORM table;

```

```mysql
UPDATE table SET col1 = val1, col2 = val2, ...;
```

```mysql
UPDATE table SET col1 = val1, col2 = val2, ...
    WHERE condition;
```

```mysql
DELETE FROM table;
```

```mysql
DELETE FROM table
    WHERE condition;
```


## 事务

```mysql
BEGIN;

    ROLLBACK;

    SAVEPOINT identifier;

    RELEASE SAVEPOINT identifier;

    ROLLBACK TO SAVEPOINT identifier;

    COMMIT;
```

```mysql
START TRANSACTION;

    ROLLBACK WORK;

    SAVEPOINT identifier;

    RELEASE SAVEPOINT identifier;

    ROLLBACK TO SAVEPOINT identifier;

    COMMIT WORK;

```

## 索引

```mysql
CREATE INDEX index ON table (col1, col2, ...);
```

```mysql
DROP INDEX index ON table;
```


## 函数

#### ASCII
#### CHAR_LENGTH or CHARACTER_LENGTH
#### CONCAT
#### CPNCAT_WS
#### FILELD
#### FIND_IN_SET
#### FORMAT
#### INSERT
#### LOCATE
#### LCASE
#### LEFT
#### LOWER
#### LPAD
#### LTRIM
#### MID
#### POSITION
#### REPEAT
#### REPLACE
#### REVERSE
#### RIGHT
#### RPAD
#### RTRIM
#### SPACE
#### STRCMP
#### SUBSTR
#### SUBSTRING
#### SUBSTRING_INDEX
#### TRIM
#### UCASE
#### UPPER

#### ABS
#### ACOS
#### ASIN
#### ATAN
#### ATAN2
#### AVG
#### CEIL
#### CEULING
#### COS
#### COT
#### COUNT
#### DEGREES
#### DIV
#### EXP
#### FLOOR
#### GREATEST
#### LEAST
#### LN
#### LOG
#### LOG10
#### LOG2
#### MAX
#### MIN
#### MOD
#### POW
#### POWER
#### RADIAN
#### RAND
#### ROUND
#### SIGN
#### SIN
#### SQRT
#### SUM
#### TAN
#### TRUNCATE

#### ADDDATE
#### ADDTIME
#### CURDATE
#### CYRRENT_DATE
#### CURRENT_TIME
#### CURRENT_TIMESTAMP
#### CURTIME
#### DATE
#### DATEDIFF
#### DATE_ADD
#### DATE_FORMAT
#### DATA_SUB
#### DAY
#### DATNAME
#### DATOFMONTH
#### DATOFWEEK
#### DATOFYEAR
#### EXTRACT
#### FROM_DAYS
#### HOUR
#### LAST_DAY
#### LOCALTIME
#### LOCALTIMESTAMP
#### MAKEDATE
#### MAKETIME
#### MICROSECOND
#### MINUTE
#### MONTHNAME
#### MONTH
#### NOW
#### PEROID_ADD
#### PERIOD_DIFF
#### QUARTER
#### SECOND
#### SEC_TO_TIME