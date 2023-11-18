# `JsonPath` Support Documentation

## Resources

* [JSONPath Syntax](https://support.smartbear.com/alertsite/docs/monitors/api/endpoint/jsonpath.html)
* [`JsonPath` by Goessner](https://goessner.net/articles/JsonPath/) (JS/PHP implementation)
* [`jayway` – a Java DSL for reading JSON documents](https://github.com/json-path/JsonPath) (Java port of Goessner's implementation)
* [JSONPath Online Evaluator - jsonpath.com](https://jsonpath.com/)
* Existing `ArduinoJson` issues relating to `JsonPath`
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
* Recursive Descent: `$.store..title`
* Wildcard (`*`)
  * Member names: `$store.book[0].*`
  * Array indices: `$.store.book[*].title`
* Array
  * Subscript (`[]`): `book[1]`
  * Indices (`[,]`)  
    * `[index1,index2,…]`  
      Selects array elements with the specified indexes
  * Slice (`[:]`)  
    * `[start:]`  
       Selects all elements from start until the end of the array
    * `[start:end]`  
      Selects array elements from the start index and up to, but not including, end index
    * `[start:end:step]` [_goessner_](https://goessner.net/articles/JsonPath/index.html#e2)
      [Array slice syntax proposal](http://developer.mozilla.org/es4/proposals/slice_syntax.html) `[start:end:step]` from [ECMASCRIPT 4](http://www.ecmascript.org/)
    * `[:n]`  
      Selects the first n elements of the array
    * `[-n:]`  
      Selects the last n elements of the array
* Filter expression (`?()`)  
  Selects all elements in an object or array that match the specified filter
* Script Expression (`()`)  
  Script expressions can be used instead of explicit property names or indexes. An example is `[(@.length-1)]` which selects the last item in an array. Here, length refers to the length of the current array rather than a JSON field named length.

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

