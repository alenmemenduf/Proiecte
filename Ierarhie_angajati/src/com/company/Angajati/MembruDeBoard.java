package com.company.Angajati;

public final class MembruDeBoard extends Angajat {
    private AsistentMembruDeBoard asistent;

    public MembruDeBoard() {
        super();
        this.typeAngajat = "MembruDeBoard";
        asistent = null;
    }

    public MembruDeBoard(String nume, int salariu,boolean vacanta) {
        super(nume, salariu,vacanta);
        this.typeAngajat = "MembruDeBoard";
        this.asistent = null;
    }
    public MembruDeBoard(String nume, int salariu, AsistentMembruDeBoard asistent,boolean vacanta) {
        super(nume, salariu,vacanta);
        this.typeAngajat = "MembruDeBoard";
        this.asistent = asistent;
    }

    public AsistentMembruDeBoard getAsistent() {
        return asistent;
    }

    public void setAsistent(AsistentMembruDeBoard asistent) {
        this.asistent = asistent;
    }
}
