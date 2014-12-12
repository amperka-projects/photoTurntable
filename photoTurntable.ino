// Характеристика двигателя,
// количество шагов на один оборот вала
#define MOTOR_STEPS_REVOLUTION 200

// Передаточный коэффициент шестерёнок
#define GEAR_COEFFICIENT 2

// Итоговое количество шагов на один оборот столика
#define STEPS_REVOLUTION GEAR_COEFFICIENT * MOTOR_STEPS_REVOLUTION

// Необходимое количество кадров за один оборот
#define SHOTS 40

// Количество шагов двигателя между снимками
#define STEPS_ON_SHOT STEPS_REVOLUTION/SHOTS

// Выдержка времени между шагами.
// Чем больше это число, тем медленнее вращается двигатель
#define DELAY_TIME 8

// Назначим пины
// Troyka-Stepper:
// Шаг двигателя
#define STEP 5 
// Направление вращения
#define DIR  6 
// Включение двигателя
#define EN   7 

// Реле. При срабатывании включает затвор фотоаппарата
#define SHOT 8

void setup() {
  // Настроим все необходимые пины на выход
  for (int i = STEP; i <= SHOT; ++i) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // Включаем мотор
  digitalWrite(EN, HIGH);

  // Для каждого из необходимого количества снимков...
  for (int i = 0; i < SHOTS; ++i) {
    // Ждём 500 мс, чтобы столик остановился
    delay(500);

    // Замыкаем реле, происходит съёмка
    digitalWrite(SHOT, HIGH);
    delay(200);
    // Размыкаем реле
    digitalWrite(SHOT, LOW);

    // Выдержка, чтобы фотоаппарат успел записать снимок на карту
    delay(1000);

    // Поворачиваем столик на необходимое количество шагов
    for (int i = 0; i < STEPS_ON_SHOT; ++i) {

      // Один шаг
      digitalWrite(STEP, HIGH);
      delay(DELAY_TIME);
      digitalWrite(STEP, LOW);
      delay(DELAY_TIME);
    }
  }

  // После завершения съёмки отключаем двигатель
  digitalWrite(EN, LOW);

  // Завершаем работу.
  // Чтобы возобновить работу нужно нажать кнопку RESET
  while (true) {
    ;
  }
}

