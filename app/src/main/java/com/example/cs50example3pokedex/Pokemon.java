package com.example.cs50example3pokedex;

public class Pokemon {

    private String name;
    private int number;

    Pokemon(String name, int number) {
        this.name = name;
        this.number = number;
    }

    public String getName() {
        return name;
    }

    public int getNumber() {
        return number;
    }
}
