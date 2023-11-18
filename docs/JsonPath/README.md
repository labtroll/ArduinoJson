# `JsonPath` Support Documentation

## Resources

* [`JsonPath` standard](https://goessner.net/articles/JsonPath/)
* Existing issues relating to `JsonPath`
  * bblanchon/ArduinoJson#821
  * bblanchon/ArduinoJson#1505
  * bblanchon/ArduinoJson#1904
  * bblanchon/ArduinoJson#1904 [`element.element` support code fragment](https://github.com/bblanchon/ArduinoJson/issues/1904#issuecomment-1498614172)
* JsonPath Syntax General
  * JSONPath square brackets operate on the _object_ or _array_ addressed by the previous path fragment
  * Indices always start by 0

## JsonPath API

## JsonPath Expressions

Reference: [JSONPath expressions](https://goessner.net/articles/JsonPath/index.html#e2)

* "Root member": `$`
* Child Operator
  * Dot notation (`.`): `$.store.book[0].title`
  * Bracket notation (`[]`): `$['store']['book'][0]['title']`
* Recursive Descent: `$store..title`
* Wildcard (`*`)
  * Member names: `$store.book[0].*`
  * Array indices: `$.store.book[*].title`
* Array
  * Subscript (`[]`): `book[1]`
  * Alternate names or array indices ((`[,]`): :warning:
  * Slice (`[start:end:step]`): :warning:
* Filter expression (`?()`): :warning:
* Script Expression (`()`): :warning:

## JsonPath API Implementation

Reference: [JSONPath implementation](https://goessner.net/articles/JsonPath/index.html#e4)

* **class JsonPath**
  * **jsonPath(obj, expr [, args])**
    * **Parameters**
      * **obj**: (object|array)  
        Object representing the JSON structure.
      * **expr** (string)  
        JSONPath expression string.
      * **args** (object|undefined)  
        Object controlling path evaluation and output. Currently only one member is supported.
      * **args.resultType** ("VALUE"|"PATH")
        causes the result to be either matching values (default) or normalized path expressions.
    * **Return Value**
      * **(array|false)**  
        :warning: alternate "no match" return value (possibly zero length array).  
        Array holding either values or normalized path expressions matching the input path expression, which can be used for lazy evaluation. false in case of no match.
   

## JsonPath Examples

Reference: [JSONPath examples](https://goessner.net/articles/JsonPath/index.html#e3)

```JSON
{ "store": {
    "book": [ 
      { "category": "reference",
        "author": "Nigel Rees",
        "title": "Sayings of the Century",
        "price": 8.95
      },
      { "category": "fiction",
        "author": "Evelyn Waugh",
        "title": "Sword of Honour",
        "price": 12.99
      },
      { "category": "fiction",
        "author": "Herman Melville",
        "title": "Moby Dick",
        "isbn": "0-553-21311-3",
        "price": 8.99
      },
      { "category": "fiction",
        "author": "J. R. R. Tolkien",
        "title": "The Lord of the Rings",
        "isbn": "0-395-19395-8",
        "price": 22.99
      }
    ],
    "bicycle": {
      "color": "red",
      "price": 19.95
    }
  }
}
```

| JSONPath | Results | Description |
| :--      | :---   | :-- |
| `$.store.book[*].author` | `["Nigel Rees", "Evelyn Waugh", "Herman Melville", "J. R. R. Tolkien"]` | the authors of all books in the store |
| `$..author` |	`["Nigel Rees", "Evelyn Waugh", "Herman Melville", "J. R. R. Tolkien"]` | all authors |
| `$.store.*` |	:warning: | all things in store, which are some books and a red bicycle. |
| `$.store..price` | `[8.95, 12.99, 8.99, 22.99, 19.95]` | the price of everything in the store. |
| `$..book[2]` |	`{"category": "fiction", "author": "Herman Melville", ...}` | the third book |
| `$..book[(@.length-1)]`<br/>`$..book[-1:]` | `{"category": "fiction", "author": "J. R. R. Tolkien", ...}` | the last book in order. |
| `$..book[0,1]`<br/>`$..book[:2]` | `[{"category": "reference", "author": "Nigel Rees", ...},`<br/>`{"category": "fiction", "author": "Evelyn Waugh", ...}]` | the first two books |
| `$..book[?(@.isbn)]` | `[{"category": "fiction", "author": "Herman Melville", ... },`<br/>`{"category": "fiction", "author": "J. R. R. Tolkien", ...}]` | filter all books with isbn number |
| `$..book[?(@.price<10)]` | `[{"category": "reference", ..., "price": 8.95}`,<br/>`{"category": "fiction", ..., "price": 8.99}]` | filter all books cheapier than 10 |
| `$..*` | :warning: | All members of JSON structure. |

