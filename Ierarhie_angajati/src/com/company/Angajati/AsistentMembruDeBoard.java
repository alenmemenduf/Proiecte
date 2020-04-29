package com.company.Angajati;

public final class AsistentMembruDeBoard extends Angajat {
    public AsistentMembruDeBoard() {
        super();
        this.typeAngajat = "AsistentMembruDeBoard";
    }

    public AsistentMembruDeBoard(String nume, int salariu,boolean vacanta) {
        super(nume, salariu,vacanta);
        this.typeAngajat = "AsistentMembruDeBoard";
    }
}
