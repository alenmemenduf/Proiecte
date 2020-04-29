package com.company.Angajati;

public class MembruDeProiect extends AngajatCuDepartament {
    protected String numeProiect;

    public MembruDeProiect() {
        super();
        this.numeProiect = null;
        this.typeAngajat = "MembruDeProiect";
    }

    public MembruDeProiect(String nume, int salariu, String departament, String numeProiect,boolean vacanta) {
        super(nume, salariu, departament,vacanta);
        this.typeAngajat = "MembruDeProiect";
        this.numeProiect = numeProiect;
    }

    public String getNumeProiect() {
        return numeProiect;
    }

    public void setNumeProiect(String numeProiect) {
        this.numeProiect = numeProiect;
    }

    @Override
    public void afisare() {
        super.afisare();
            System.out.println("numele proiectului: " + numeProiect);
    }

}
