package com.company.Angajati;
import java.util.*;

public final class ManagerDeProiect extends MembruDeProiect {

    public ManagerDeProiect() {
        super();
        this.typeAngajat = "ManagerDeProiect";
    }

    public ManagerDeProiect(String nume, int salariu, String departament, String numeProiect,boolean vacanta) {
        super(nume, salariu, departament, numeProiect,vacanta);
        this.typeAngajat = "ManagerDeProiect";
    }
}
