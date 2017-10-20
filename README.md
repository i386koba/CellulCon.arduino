# CellulCon.arduino　（セラコンのマイコン部）
* ラジコンに乗せたスマフォのBluetoothから送信される操作コマンドを受信してサーボを動かすためのArduinoスケッチです。
* このソース単体ではセラコン動きません。セルコン プロジェクト全体は https://github.com/cellucon/ より参照ください。

## Bluetoothを受信するArduinoベースのマイコン
* Arduinoで手作りする場合の参考 https://github.com/i386koba/Droidrone-ino
* スマフォとはBluetooth 2.x の SPPでシリアル通信します。
* Arduinoベース専用マイコン基板（KiCAD） https://github.com/i386koba/CelluCon.kicad

## スマートフォンを乗せるラジコン
![image](https://github.com/cellucon/readme/blob/master/rover.png)
* TAMIYAのグラスホッパー、完成品を購入して、スマフォをつける改造しました。完成品はプロポが余ります。
* ラジコンの心得のある人なら完成品でなく、シャーシキットとサーボとESCを別購入すればあれば安上がりでプロポが余りません。
* 100円ショップにある車用スマフォホルダーなどでスマフォをラジコンに固定します。

## 技術情報は
* wikiにアップしていきます。　https://github.com/i386koba/CellulCon.arduino/wiki
* https://i386koba.github.io/CelluCon.web/ からセラコン操作Web画面を開けます。
