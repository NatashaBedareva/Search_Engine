# search_engine
### Поисковая система по файлам
---
# Описание

Поисковая система для локальных файлов. Поиск выполняется в соответствии с указанными параметрами (config.json) и выводит результат в конечный файл answers.json   
Принцип работы:  
1. В файле config.json нужно указать пути к файлам, по которым будет вестить поиск.  
2. Поисковая система самостоятельно обходит все файлы и индексирует их.  
3. Пользователь задает запрос с помощью файла requests.json. Запрос представляет собой набор слов для поиска документов.  
4. Запрос преобразуется в список слов.  
5. Далее происходит поиск слов в файлах, создаётся частотный словарь и подсчитывается реаливатность файлов.  
6. Результат поиска вывадтся в answers.json  

# Методы
## ConverterJSON
● std::vector<std::string> GetTextDocuments() считывает конфигурационные данные из JSON,  
● std::vector<std::string> GetRequests() преобразовывает запросы в формате JSON,  
● void putAnswers(std::vector<std::vector<RelativeIndex>> answers) формирует ответы в заданном формате JSON.  

## InvertedIndex
● void UpdateDocumentBase(std::vector<std::string> input_docs) считывает файлы, полученные из файла конфигурации, создает список слов, а также подсчитывает их количество, индексируя по документам  
● void GetWordCount(std::string word) метод определяет количество вхождений слова word в загруженной базе документов. word слово, частоту вхождений которого необходимо определить  

## SearchServer
● std::vector<std::vector<RelativeIndex>> Search(std::vector<std::string> queries_input, std::vector<std::string> text_documents) метод обработки поисковых запросов. Возвращает отсортированный список релевантных ответов для заданных запросов  

# Начало работы
1. Создайте три файла config.json answers.json requests.json  
2. В классе ConverterJSON в методах GetTextDocuments(),GetResponsesLimit(),GetRequests(),putAnswers() укажите пути к данным файлам  

Пример файла config.json
```
{
  "config": {
    "name": "SearchEngine",
    "version": "0.1",
    "max_responses": 7
  },
  "files": [
    "resources/text01.txt",
    "resources/text02.txt",
    "resources/text03.txt",
    "resources/text04.txt",
    "resources/text05.txt"
  ]
}
```

Пример файла requests.json
```
{
  "requests": [
    "curabitur",
    "in the",
    "non"
  ]
}
```
Затем запустите SearchEngine, результатом работы приложения будет файл answers.json, содержащий список найденных слов, id документов с найдеными словами и их реливатность.
