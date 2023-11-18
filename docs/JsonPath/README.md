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

* Root member (`$`)
* Child Operator
  * Dot notation (`.`): `$.store.book[0].title`
  * Bracket notation (`[]`): `$['store']['book'][0]['title']`
    * `['<name1>' (, '<name2>')]`: `$.['store']['book', 'bicycle']['price']`  
      Bracket-notated child or children[^1]
* Recursive Descent (`..`): `$.store..title`
* Wildcard (`*`)
  * Member names: `$.store.book[0].*`
  * Array indices: `$.store.book[*].title`
* Array
  * Subscript (`[]`): `book[1]`
  * Indices (`[,]`)  
    * `[index1 (, index2)]`:  `book[1, 2, 4]`  
      Selects array elements with the specified indices
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
  Selects all elements in an object or array that match the specified filter.  
  An expression that specifies just a property name, such as `[?(@.isbn)]`, matches all items that have this property, regardless of the value.
* Script Expression (`()`)  
  Script expressions can be used instead of explicit property names or indexes. An example is `[(@.length-1)]` which selects the last item in an array. Here, length refers to the length of the current array rather than a JSON field named length.

## JsonPath Functions and Operators

Reference: [JsonPath](https://github.com/json-path/JsonPath#functions)

| Function	| Description	| Output type |
| :--      | :--         | :--         |
| `min()`	| Provides the min value of an array of numbers	| Double
| `avg()`	|	Provides the average value of an array of numbers |	Double
| `stddev()`	|	Provides the standard deviation value of an array of numbers |	Double
| `length()`	|	Provides the length of an array |	Integer
| `sum()`	|	Provides the sum value of an array of numbers |	Double
| `keys()`	|	Provides the property keys (An alternative for terminal tilde ~) |	Set<E>
| `concat(X)`	|	Provides a concatenated version of the path output with a new item |	like input
| `append(X)`	|	add an item to the json path output array |	like input
| `first()`	|	Provides the first item of an array |	Depends on the array
| `last()`	|	Provides the last item of an array |	Depends on the array
| `index(X)`	|	Provides the item of an array of index: X, if the X is negative, take from backwards	| Depends on the array
| Filter Operators |

Filters are logical expressions used to filter arrays. A typical filter would be `[?(@.age > 18)]` where @ represents the current item being processed. More complex filters can be created with logical operators `&&` and `||`. String literals must be enclosed by single or double quotes (`[?(@.color == 'blue')]` or `[?(@.color == "blue")]`).

| Operator	| Description |
| :--      | :--         |
| `==`	| left is equal to right (note that 1 is not equal to '1')
| `!=` |	left is not equal to right
| `<`	|	left is less than right
| `<=`	|	left is less or equal to right
| `>`	|	left is greater than right
| `>=`	|	left is greater than or equal to right
| `=~`	|	left matches regular expression `[?(@.name =~ /foo.*?/i)]`
| `in`	|	left exists in right `[?(@.size in ['S', 'M'])]`
| `nin`	|	left does not exists in right
| `subsetof`	|	left is a subset of right `[?(@.sizes subsetof ['S', 'M', 'L'])]`
| `anyof`	|	left has an intersection with right `[?(@.sizes anyof ['M', 'L'])]`
| `noneof`	|	left has no intersection with right `[?(@.sizes noneof ['M', 'L'])]`
| `size`	|	size of left (array or string) should match right
| `empty`	|	left (array or string) should be empty

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

[^1]: https://github.com/json-path/JsonPath#operators
