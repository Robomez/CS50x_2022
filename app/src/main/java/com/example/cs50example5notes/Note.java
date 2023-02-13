package com.example.cs50example5notes;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.PrimaryKey;

@Entity(tableName = "notes")
public class Note {
    @PrimaryKey
    public int id;

    @ColumnInfo(name = "contents")
    public String contents;
}
