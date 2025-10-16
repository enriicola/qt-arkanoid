# What Qt is (and why it matters)

Qt (“cute”) is a **cross-platform C++ application framework** used to build native, high-performance apps for **desktop, mobile, and embedded**. Think: one codebase, multiple OSes (Linux, Windows, macOS, Android, iOS, embedded Linux). Beyond GUI, Qt gives you batteries-included libraries for **networking, threads, file I/O, JSON/XML, SQL, graphics**, etc. It’s modular: core types live in **QtCore**, UIs in **QtWidgets** (classic desktop) or **Qt Quick/QML** (declarative UIs), plus add-on modules (Network, Multimedia, SerialPort…). ([doc.qt.io][1])

## Two UI stacks (you should know both)

* **Qt Widgets (C++):** traditional desktop controls (QPushButton, QTableView…). Good for classic apps and tooling. Uses **signals/slots**, **event loop**, and **Model/View** for data-driven lists/tables/trees. ([doc.qt.io][2])
* **Qt Quick / QML (declarative):** modern, animated UIs described in **QML** with JS logic, often combined with C++ backends for performance. Great for touch/embedded/mobile and fluid UIs. ([doc.qt.io][3])

## Core ideas you’ll get asked about

* **Signals & Slots:** Qt’s type-safe pub/sub for object communication. Decouples UI from logic; connections can be queued across threads. Expect to explain how and when they fire. ([doc.qt.io][4])
* **Event Loop & QObject:** objects live on a thread with an event loop; timers, I/O, and queued signals are processed there. ([doc.qt.io][5])
* **Model/View:** separates data (model) from presentation (view); e.g., QAbstractItemModel powering QListView/QTableView. ([doc.qt.io][2])
* **Threads in Qt:** prefer **worker-object + QThread** (moveToThread) instead of subclassing QThread for logic; understand object/thread affinity and cleanup rules. ([doc.qt.io][5])
* **Build system:** **CMake** with `find_package(Qt6 ...)` and `target_link_libraries(mytarget Qt6::Widgets …)`. Know `CMAKE_PREFIX_PATH` if CMake can’t find Qt. ([doc.qt.io][6])
* **Networking:** `QNetworkAccessManager` for HTTP; request/response with signals; typically one manager per app. ([doc.qt.io][7])
* **Tools:** **Qt Creator** (IDE), Designer/Forms, Kits/Toolchains. ([doc.qt.io][8])
* **Licensing at a glance:** Open-source (GPL/LGPL) and commercial options. You just need to know that both exist. ([Wikipedia][9])

## Micro-snippets you can recognize in an interview

### 1) Minimal Widgets app + signal/slot (Qt6 + CMake)

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(hello_qt LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
add_executable(hello main.cpp)
target_link_libraries(hello PRIVATE Qt6::Widgets)
```

```cpp
// main.cpp
#include <QApplication>
#include <QPushButton>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  QPushButton btn("Hello Qt");
  QObject::connect(&btn, &QPushButton::clicked, &app, &QApplication::quit);
  btn.show();
  return app.exec();
}
```

(Shows signal/slot connection and the event loop.) ([doc.qt.io][6])

### 2) QML “Hello” + integrate C++

```qml
// main.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
ApplicationWindow {
  visible: true; width: 320; height: 200; title: "Hi"
  Button { text: "Click me"; onClicked: console.log("clicked") }
}
```

(Usually launched via a `QQmlApplicationEngine` in C++.) ([doc.qt.io][3])

### 3) Worker-object with QThread (pattern you can describe)

* Create `Worker : public QObject` with slots/doWork.
* Create `QThread`, `worker->moveToThread(thread)`.
* Connect a start signal to `Worker::doWork`, and `finished` to `thread->quit()`.
  This is the recommended pattern and a common interview topic. ([doc.qt.io][5])

## A tight study path (2–3 focused evenings)

### 1) Big picture & install

* Qt Docs Home → *Get started / New to Qt* (what Qt is, modules, examples). ([doc.qt.io][1])
* Qt Creator → *Getting Started* + *Tutorials* (create, run, debug a sample). ([doc.qt.io][8])

### 2) Widgets first

* *Signals & Slots* overview. Re-implement the minimal app above. ([doc.qt.io][4])
* *Model/View Programming* (scan concepts + try a `QStandardItemModel` with `QTableView`). ([doc.qt.io][2])

### 3) QML/Qt Quick (know the story)

* Qt Quick overview + QML basics to explain when you’d choose it over Widgets. ([doc.qt.io][3])

### 4) Threads & networking

* QThread docs + KDAB “Eight Rules of Multithreaded Qt” (best practices). ([doc.qt.io][5])
* `QNetworkAccessManager` quick read; write a tiny GET example. ([doc.qt.io][7])

### 5) Build tooling

* *Getting started with CMake* for Qt 6 (know `find_package`, `Qt6::Widgets`, `CMAKE_PREFIX_PATH`). ([doc.qt.io][6])

## Curated sources (official & battle-tested)

* **Qt Docs Home (official portal).** Framework overview, modules, and examples. ([doc.qt.io][1])
* **Signals & Slots (official).** Clear, canonical explanation. ([doc.qt.io][4])
* **Qt Quick / QML (official).** What QML is, when to use it. ([doc.qt.io][3])
* **Model/View Programming (official).** The pattern behind lists/tables/trees. ([doc.qt.io][2])
* **QThread (official).** Threading model, event loop in threads, worker pattern. ([doc.qt.io][5])
* **KDAB: The Eight Rules of Multithreaded Qt.** Practical pitfalls & fixes (top industry source). ([KDAB][10])
* **CMake + Qt6 (official).** Minimal, modern build setup. ([doc.qt.io][6])
* **Qt Creator: Getting Started & Tutorials.** IDE basics and guided examples. ([doc.qt.io][8])
* **QNetworkAccessManager (official).** HTTP requests with signals/replies. ([doc.qt.io][7])
* **Wikipedia: Qt (software).** Quick background, current major release, licensing. (Use for context; rely on Qt docs for API.) ([Wikipedia][9])

---

If you want, I can spin up a tiny **practice checklist** (widgets app, one QML app, one network call, one threaded worker) and some “interview-style” questions with short, clean answers.

[1]: https://doc.qt.io/?utm_source=chatgpt.com "Qt Documentation | Home"
[2]: https://doc.qt.io/qt-6/model-view-programming.html?utm_source=chatgpt.com "Model/View Programming | Qt Widgets | Qt 6.9.3"
[3]: https://doc.qt.io/qt-6/qtquick-index.html?utm_source=chatgpt.com "Qt Quick | Qt 6.9.3"
[4]: https://doc.qt.io/qt-6/signalsandslots.html?utm_source=chatgpt.com "Signals & Slots | Qt Core | Qt 6.9.3"
[5]: https://doc.qt.io/qt-6/qthread.html?utm_source=chatgpt.com "QThread Class | Qt Core | Qt 6.9.3"
[6]: https://doc.qt.io/qt-6/cmake-get-started.html?utm_source=chatgpt.com "Getting started with CMake"
[7]: https://doc.qt.io/qt-6/qnetworkaccessmanager.html?utm_source=chatgpt.com "QNetworkAccessManager Class | Qt Network | Qt 6.9.2"
[8]: https://doc.qt.io/qtcreator/creator-getting-started.html?utm_source=chatgpt.com "Getting Started | Qt Creator Documentation"
[9]: https://en.wikipedia.org/wiki/Qt_%28software%29?utm_source=chatgpt.com "Qt (software)"
[10]: https://www.kdab.com/the-eight-rules-of-multithreaded-qt/?utm_source=chatgpt.com "The Eight Rules of Multithreaded Qt"

## What you’ll learn, concretely

* **Qt Quick structure** (imports, items, bindings)
* **Game loop** with `Timer`, frame-based updates
* **Input** via `Keys`
* **Collision math** and simple reflection
* **Data-driven UI** (HUD bound to score/lives)
* **Reusable components** (turn bricks/paddle into QML Components later)
* **Optional C++ hooks** (expose a `GameController` to QML)

TODO: extend this with: sound effects, high-score saving, a JSON level loader in C++, and a tiny `QAbstractListModel` for a high-score table.

## my notes

* qrc -> qt resource collection = tells Qt to bundle these files into the executable
* qresource, put between tags, is a collection of resources
* file, put between tags, is the qml file to include (we can access it using 'qrc:/src/main.qml')
