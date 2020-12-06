/*
 * main.cpp - Example code using the jonblack/arduino-menusystem@^3.0.0 library
 *
 * This example shows using the menu system with a Adafruit 3.5" 480x320 TFT FeatherWing
 * (controlled over serial).
 *
 * Copyright (c) 2016 souaremsaidou 
 * Licensed under the MIT license (see LICENSE)
 */

#include <Wire.h>
#include <MenuSystem.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>

#define TFT_CS 15
#define TFT_DC 33
#define SD_CS 14

Adafruit_HX8357 lcd = Adafruit_HX8357(TFT_CS, TFT_DC, -1);

// Renderer

class MyRenderer : public MenuComponentRenderer
{
public:
    void render(Menu const &menu) const
    {
        lcd.setCursor(0, 0);
        menu.render(*this);
        menu.get_current_component()->render(*this);
    }

    void render_menu_item(MenuItem const &menu_item) const
    {
        lcd.setCursor(0, 1 * 8);
        lcd.print(menu_item.get_name());
    }

    void render_back_menu_item(BackMenuItem const &menu_item) const
    {
        lcd.setCursor(0, 1 * 8);
        lcd.print(menu_item.get_name());
    }

    void render_numeric_menu_item(NumericMenuItem const &menu_item) const
    {
        lcd.setCursor(0, 1 * 8);
        lcd.print(menu_item.get_name());
    }

    void render_menu(Menu const &menu) const
    {
        lcd.setCursor(0, 0 * 8);
        lcd.print(menu.get_name());
    }
};
MyRenderer my_renderer;

// Menu callback function

void on_item1_selected(MenuComponent *p_menu_component)
{
    lcd.setCursor(0, 2 * 8);
    lcd.print("Item1 Selectd");
    // lcd.display();
    lcd.fillScreen(HX8357_BLACK);
    delay(1500); // so we can look the result on the LCD
}

void on_item2_selected(MenuComponent *p_menu_component)
{
    lcd.setCursor(0, 2 * 8);
    lcd.print("Item2 Selectd");
    // lcd.display();
    lcd.fillScreen(HX8357_BLACK);
    delay(1500); // so we can look the result on the LCD
}

void on_item3_selected(MenuComponent *p_menu_component)
{
    lcd.setCursor(0, 2 * 8);
    lcd.print("Item3 Selectd");
    lcd.fillScreen(HX8357_BLACK);
    delay(1500); // so we can look the result on the LCD
}

// Menu variables

MenuSystem ms(my_renderer);
MenuItem mm_mi1("Lvl1-Item1(I)", &on_item1_selected);
MenuItem mm_mi2("Lvl1-Item2(I)", &on_item2_selected);
Menu mu1("Lvl1-Item3(M)");
MenuItem mu1_mi1("Lvl2-Item1(I)", &on_item3_selected);

void serial_print_help()
{
    Serial.println("***************");
    Serial.println("w: go to previus item (up)");
    Serial.println("s: go to next item (down)");
    Serial.println("a: go back (right)");
    Serial.println("d: select \"selected\" item");
    Serial.println("?: print this help");
    Serial.println("h: print this help");
    Serial.println("***************");
}

void serial_handler()
{
    char inChar;
    if ((inChar = Serial.read()) > 0)
    {
        switch (inChar)
        {
        case 'w': // Previus item
            ms.prev();
            ms.display();
            break;
        case 's': // Next item
            ms.next();
            ms.display();
            break;
        case 'a': // Back pressed
            ms.back();
            ms.display();
            break;
        case 'd': // Select pressed
            ms.select();
            ms.display();
            break;
        case '?':
        case 'h': // Display help
            serial_print_help();
            break;
        default:
            break;
        }
    }
}

// Standard arduino functions

void setup()
{
    Serial.begin(9600);
    lcd.begin();
    // lcd.setContrast(60); // TODO:

    lcd.setRotation(1);
    lcd.fillScreen(HX8357_RED);
    delay(2000);

    lcd.setTextSize(10);

    serial_print_help();

    ms.get_root_menu().add_item(&mm_mi1);
    ms.get_root_menu().add_item(&mm_mi2);
    ms.get_root_menu().add_menu(&mu1);
    mu1.add_item(&mu1_mi1);
    ms.display();
}

void loop()
{
    serial_handler();
}