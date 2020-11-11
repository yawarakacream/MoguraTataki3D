#include "SegmentDisplay.hpp"
#include "Panel.hpp"

#define GAMETIME 20000 // 制限時間, 単位: ミリ秒
#define TARGET_SIZE 2 // ターゲットの数

// #define BUTTON 13
#define DISPLAY_R A8, A9, A10, A11, A12, A13, A14
#define DISPLAY_L A0, A1, A2, A3, A4, A5, A6

#define UNUSED_ANALOGPIN A15

const Panel panels[] = { Panel(22, 23, 24, 160), Panel(26, 27, 28, 140), Panel(30, 31, 32, 175), Panel(34, 35, 36, 175),
  Panel(38, 39, 40, 150), Panel(42, 43, 44, 300) };
const int PANELS_SIZE = sizeof(panels) / sizeof(panels[0]); // パネルの数は1以上と決め打ち

// 0: 左, 1: 右
const SegmentDisplay displays[2] = { SegmentDisplay( (int[]) { DISPLAY_L }, false), SegmentDisplay( (int[]) { DISPLAY_R }, true) };

int score;

volatile bool buttonPushed = false;

void setup() {

  /*
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(BUTTON, onButtonPushed, FALLING);
  */

  Serial.begin(9600);

  randomSeed(analogRead(UNUSED_ANALOGPIN));

}

void loop() {

  reset();
  standby();
  reset();
  game();
  
  /*
   * ボタンが押されるまで点数を表示し続ける
   */
  // standby();

}

void reset() {
  
  setSegmentDisplay(score = 0);

  for (int i = 0; i < PANELS_SIZE; i++)
    panels[i].setTarget(false);
  
}

void standby() {
  
  // ボタンが押されるまでパネルでイルミネーション

  int illuminationArraySize = PANELS_SIZE / 3;
  unsigned long illumination = millis();
  int wave;

  while (!isButtonPushed()) {

    for (int i = 0; i < PANELS_SIZE; i++) {

      panels[PANELS_SIZE <= i + 1 ? 0 : i + 1].setLED(true);
      panels[i].setLED(true);
      panels[i - 1 < 0 ? PANELS_SIZE - 1 : i - 1].setLED(false);

      if (PANELS_SIZE < ++wave)
        wave = 0;
        
      while (millis() - illumination < 200);
        
      illumination = millis();

    }
      
  }

}

void game() {

  // 最初のターゲットを選ぶ
  for (int i = 0; i < TARGET_SIZE; i++) {

    while (true) {
      
      int j = random(PANELS_SIZE);
        
      if (panels[j].isTarget())
        continue;

      panels[j].setTarget(true);

      break;
      
    }
    
  }

  // unsigned long startTime = millis();
    
  while (true) {

    if (isButtonPushed())
      break;
      
    for (int i = 0; i < PANELS_SIZE; i++) {

      if (!panels[i].isTarget() || !panels[i].check())
        continue;
      
      panels[i].setTarget(false);

      setSegmentDisplay(++score);

      // 次のターゲットを選ぶ
      while (true) {

        int next = random(PANELS_SIZE);
        
        if (panels[next].isTarget() || panels[i].equals(panels[next]))
          continue;
        
        panels[next].setTarget(true);

        break;

      }

      delay(1);

    }

    /*if (GAMETIME < millis() - startTime)
      break;*/

  }

}

void setSegmentDisplay(int value) {

  displays[1].setValue(value % 10);
  displays[0].setValue(value / 10 % 10);

}

void onButtonPushed() {
  buttonPushed = true;
}

bool isButtonPushed() {
  
  if (buttonPushed) {
    return !(buttonPushed = false);
  }

  return false;

}

