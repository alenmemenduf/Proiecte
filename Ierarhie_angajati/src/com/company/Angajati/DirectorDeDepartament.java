package com.company.Angajati;

public final class DirectorDeDepartament extends AngajatCuDepartament {
    public DirectorDeDepartament() {
        super();
        this.typeAngajat = "DirectorDeDepartament";
    }
    public DirectorDeDepartament(String nume, int salariu, String departament,boolean vacanta) {
        super(nume, salariu, departament,vacanta);
        this.typeAngajat = "DirectorDeDepartament";
    }

}
