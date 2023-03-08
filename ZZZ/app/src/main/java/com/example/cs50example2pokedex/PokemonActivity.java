package com.example.cs50example2pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import java.util.Locale;

public class PokemonActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);

        TextView nameTextView = findViewById(R.id.pokemon_name);
        TextView numberTextView = findViewById(R.id.pokemon_number);

        String name = getIntent().getStringExtra("name");
        int number = getIntent().getIntExtra("number", 0);

        nameTextView.setText(name);
        numberTextView.setText(String.format(Locale.ENGLISH, "#%03d", number));
    }
}