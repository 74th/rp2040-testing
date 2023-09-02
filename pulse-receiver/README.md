# Pulse Receiver

エアコンの信号長が長くて、ESP32C3 の CircuitPython の PulseIn で受信できないので、RP2040 で受信部のみを実装。

USB CDC で受信結果をみる。
得られた pulse は https://github.com/74th/esp32c3-ir-server に投げつけられる。

## 使う物

M5Stack 用赤外線受信ユニット https://www.switch-science.com/products/5699

これを、5V、GND と、DATA IN を GPIO8 につなぐ。
