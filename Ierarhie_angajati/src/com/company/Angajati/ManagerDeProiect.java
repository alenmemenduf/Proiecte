package com.company.Angajati;
import java.util.*;

public final class ManagerDeProiect extends MembruDeProiect {

    public ManagerDeProiect() {
        super();
        this.typeAngajat = "ManagerDeProiect";
    }

    public ManagerDeProiect(String nume, int salariu, String departament, String numeProiect) {
        super(nume, salariu, departament, numeProiect);
        this.typeAngajat = "ManagerDeProiect";
    }
}
