lv_obj_t* label;
void opcontrol() {
    // you can still do whatever screen setup you want in initialize
    label = lv_label_create(lv_scr_act(), NULL);
    while (true) {
         // Do stuff
        auto txt = "actual velocity: " + std::to_string(flywheel.get_actual_velocity());
        lv_label_set_text(label, txt.c_str());
        delay(20);
    }
}
