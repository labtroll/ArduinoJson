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

## JsonPath Syntax Support Priority

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

## JsonPath Examples

(from [JSONPath examples](https://goessner.net/articles/JsonPath/index.html#e3))

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

| JSONPath | Result |
| :--      | :---   |
| `$.store.book[*].author` | the authors of all books in the store
| `$..author` |	all authors
| `$.store.*` |	all things in store, which are some books and a red bicycle.
| `$.store..price| the price of everything in the store.
| `$..book[2]` |	the third book
| `$..book[(@.length-1)]`<br/>`$..book[-1:]` | the last book in order.
| `$..book[0,1]`<br/>`$..book[:2]` | the first two books
| `$..book[?(@.isbn)]` | filter all books with isbn number
| `$..book[?(@.price<10)]` | filter all books cheapier than 10
| `$..*` | All members of JSON structure.

