package com.company.Angajati;

public final class DirectorDeCanal extends AngajatCuDepartament {
    private String numeleCanalului;

    public DirectorDeCanal() {
        super();
        this.typeAngajat = "DirectorDeCanal";
        this.numeleCanalului = null;
    }

    public DirectorDeCanal(String nume, int salariu, String departament, String numeleCanalului,boolean vacanta) {
        super(nume, salariu, departament,vacanta);
        this.typeAngajat = "DirectorDeCanal";
        this.numeleCanalului = numeleCanalului;
    }

}
