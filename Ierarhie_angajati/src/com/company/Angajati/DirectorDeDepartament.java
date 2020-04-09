package com.company.Angajati;

public final class DirectorDeDepartament extends AngajatCuDepartament {
    public DirectorDeDepartament() {
        super();
        this.typeAngajat = "DirectorDeDepartament";
    }
    public DirectorDeDepartament(String nume, int salariu, String departament) {
        super(nume, salariu, departament);
        this.typeAngajat = "DirectorDeDepartament";
    }

}
