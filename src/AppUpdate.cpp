#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {

    // TODO: Add your own logics to finish the tasks in README.md
    // Task 2: Make the giraffe move into the red area using the keyboard
    auto giraffe_pos = m_Giraffe->GetPosition();
    if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
        giraffe_pos.y += 5;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        giraffe_pos.x -= 5;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
        giraffe_pos.y -= 5;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
        giraffe_pos.x += 5;
    }
    m_Giraffe->SetPosition(giraffe_pos);

    // Task 3: Make the chest disappear when the giraffe touches it
    if (m_Giraffe->IfCollides(m_Chest)) {
        m_Chest->SetVisible(false);
    }

    // Task 4: Write a program to give your bee friend an animation
    if (!m_Bee->IsLooping()) {
        m_Bee->SetLooping(true);
    }
    if (!m_Bee->IsPlaying()) {
        m_Bee->Play();
    }

    // Task 5: Open each door when the giraffe touches it
    for (const auto& door : m_Doors) {
        if (door->GetVisibility() && m_Giraffe->IfCollides(door)) {
            door->SetImage(GA_RESOURCE_DIR"/Image/Character/door_open.png");
        }
    }

    // Task 6: Design a program to countdown, stop animation after OK display
    if (m_Phase == Phase::COUNTDOWN) {
        if (m_Ball->IfAnimationEnds()) {
            m_Ball->SetVisible(false);
        } else {
            m_Ball->SetVisible(true);
            if (!m_Ball->IsPlaying()) {
                m_Ball->Play();
            }
        }
    }

    /*
     *  Do not touch the code below as they serve the purpose for validating the tasks,
     *  rendering the frame, and exiting the game.
    */

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
            ValidTask();
        }
    }
    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

    m_Root.Update();
}