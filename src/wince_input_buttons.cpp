#if defined(UNDER_CE)

// Headers
#include "input_buttons.h"
#include "keys.h"

void Input::InitButtons() {
	buttons.resize(BUTTON_COUNT);

    buttons[UP].push_back(Keys::K);
	buttons[UP].push_back(Keys::KP8); //UP
	buttons[UP].push_back(Keys::W);
    buttons[DOWN].push_back(Keys::J);
	buttons[DOWN].push_back(Keys::KP2); //DOWN
	buttons[DOWN].push_back(Keys::S);
    buttons[LEFT].push_back(Keys::H);
	buttons[LEFT].push_back(Keys::KP4); //LEFT
	buttons[LEFT].push_back(Keys::A);
    buttons[RIGHT].push_back(Keys::L);
	buttons[RIGHT].push_back(Keys::KP6); //RIGHT
	buttons[RIGHT].push_back(Keys::D);
    buttons[DECISION].push_back(Keys::Z);
	buttons[DECISION].push_back(Keys::Y);
	buttons[DECISION].push_back(Keys::SPACE);
	buttons[DECISION].push_back(Keys::RETURN); //決定
    buttons[CANCEL].push_back(Keys::X);
	buttons[CANCEL].push_back(Keys::C);
	buttons[CANCEL].push_back(Keys::V);
	buttons[CANCEL].push_back(Keys::B);
	buttons[CANCEL].push_back(Keys::N);
    buttons[CANCEL].push_back(Keys::ESCAPE); //戻る
    buttons[SHIFT].push_back(Keys::KP9); //前見出し
    buttons[N0].push_back(Keys::KP3); //次見出し
    buttons[N1].push_back(Keys::F1); //一括検索
	buttons[N2].push_back(Keys::F2); //広辞苑
	buttons[N3].push_back(Keys::F3); //英和・和英
	buttons[N4].push_back(Keys::F4); //古語
	buttons[N5].push_back(Keys::F5); //ブリタニカ
	buttons[N6].push_back(Keys::F6); //切替
	buttons[N7].push_back(Keys::F7); //しおり
	buttons[N8].push_back(Keys::F10); //Home
	buttons[N9].push_back(Keys::CAPSLOCK); //機能　不使用
    buttons[N9].push_back(Keys::KP7); //辞書メニュー
    buttons[BACKSPACE].push_back(Keys::BACKSPACE); //後退
}

#endif