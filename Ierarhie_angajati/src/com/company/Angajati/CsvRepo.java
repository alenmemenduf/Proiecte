package com.company.Angajati;

import java.io.FileWriter;
import java.io.PrintWriter;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CsvRepo {
    private static CsvRepo instance;

    private CsvRepo() { }

    public static CsvRepo getInstance() {
        if (instance == null) {
            synchronized (CsvRepo.class) {
                if (instance == null) {
                    instance = new CsvRepo();
                }
            }
        }
        return instance;
    }

    @SuppressWarnings("unchecked")
    public <T> List<T> read(String path, Class<T> type) throws Exception{
        List<T> records = new ArrayList<T>();
        List<Field> fields = new ArrayList<>();
        Constructor<T> constructor = type.getDeclaredConstructor();

        getAllFields(fields,type);
        constructor.setAccessible(true);
        for (int i=0;i<fields.size();i++) {
            if(fields.get(i).getName().equals("nrAngajati")) {
                fields.remove(i);
                i--;
            }
            else{
                fields.get(i).setAccessible(true);
            }
        }
        for (String line : Files.readAllLines(Paths.get(path))) {
            T record = constructor.newInstance();
            String[] values = line.split(",");
            if (values.length == fields.size()) {
                for (int i = 0; i < fields.size(); i++) {
                    setField(record, fields.get(i), values[i]);
                }
            }
            records.add(record);
        }
        return records;
    }

public <T> void write(List<T> records, String path) throws Exception {
    List<Field> fields = new ArrayList<>();
    getAllFields(fields,records.get(0).getClass());
    for(int i=0;i<fields.size();i++) {
        if(fields.get(i).getName().equals("nrAngajati")) {
            fields.remove(i);
            i--;
        }
        else
            fields.get(i).setAccessible(true);
    }
    try (PrintWriter writer = new PrintWriter(path)) {
        for (T record : records) {
            for (int i = 0; i < fields.size() - 1; i++) {
                Object value = fields.get(i).get(record);
                if (value != null) {
                    writer.print(value);
                }
                writer.print(",");
            }
            Object value = fields.get(fields.size() - 1).get(record);
            if (value != null) {
                writer.println(value);
            }
        }
    }
}
    public static List<Field> getAllFields(List<Field> fields, Class<?> type) { // getDeclaredFields nu returneaza si field-urile inherited

        if (type.getSuperclass() != null) {
            getAllFields(fields, type.getSuperclass());
        }
        fields.addAll(Arrays.asList(type.getDeclaredFields()));
        return fields;
    }

    private void setField(Object object, Field field, String text) throws Exception {
        if (text.isEmpty()) {
            return;
        }
        Object value = null;
        if (String.class.equals(field.getType())) {
            value = text;
        } else {
            String name=Character.toUpperCase(field.getType().getSimpleName().charAt(0)) + field.getType().getSimpleName().substring(1);
            Class<?> type = Class.forName("java.lang." + name + (int.class.equals(field.getType()) ? "eger" : ""));
            Method method = type.getDeclaredMethod("parse" + name, String.class);
            value = method.invoke(null, text);
        }
        field.set(object, value);
    }
    public void Logger(String message) throws Exception
    {
        String textToAppend = message;
        FileWriter fileWriter = new FileWriter("./Logger.csv", true); //Set true for append mode
        PrintWriter printWriter = new PrintWriter(fileWriter);
        printWriter.println(textToAppend);  //New line
        printWriter.close();
    }
}

