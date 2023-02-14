package com.example.cs50example5notes;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.EditText;

public class NoteActivity extends AppCompatActivity {

    private EditText editText;
    private int id;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_note);

        editText = findViewById(R.id.note_edit_text);
        id = getIntent().getIntExtra("id", 0);

        String contents = getIntent().getStringExtra("contents");
        editText.setText(contents);
    }

    @Override
    protected void onPause() {
        super.onPause();

        MainActivity.database.noteDao().save(String.valueOf(editText.getText()), id);
    }
}