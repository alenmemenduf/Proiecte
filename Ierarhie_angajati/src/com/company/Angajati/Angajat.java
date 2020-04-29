package com.company.Angajati;

import java.util.Comparator;

public class Angajat implements Comparable<Angajat> {
    protected String nume;
    protected String typeAngajat;
    protected static int nrAngajati;
    protected int idAngajat;
    protected int salariu;
    protected boolean vacanta;

    public Angajat(){
        this.typeAngajat = "Angajat";
        this.nume = null;
        this.salariu = 0;
        this.vacanta = false;

        synchronized(this){
            this.idAngajat = nrAngajati;
            nrAngajati++;
        }
    }
    public Angajat(String nume, int salariu, boolean vacanta) {
        this.typeAngajat = "Angajat";
        this.nume = nume;
        this.salariu = salariu;
        this.vacanta = vacanta;

        synchronized(this){
            this.idAngajat = nrAngajati;
            nrAngajati++;
        }
    }

    public String getNume() {
        return nume;
    }

    public static int getNrAngajati() {
        return nrAngajati;
    }

    public int getSalariu() {
        return salariu;
    }

    public int getIdAngajat() {
        return idAngajat;
    }

    public String getTypeAngajat() {
        return typeAngajat;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public void setSalariu(int salariu) {
        this.salariu = salariu;
    }

    public void afisare(){
        System.out.println("nume: " + nume);
        System.out.println("salariu: " + salariu);
        System.out.println("ID angajat: " + idAngajat);
        System.out.println("Functia angajatului: " + typeAngajat);
        if(this.vacanta)
            System.out.println("ANGAJATUL SE AFLA IN VACANTA!");
    }

    public void setVacanta(boolean vacanta) {
        this.vacanta = vacanta;
    }

    public boolean getVacanta() {
        return vacanta;
    }


    @Override
    public int compareTo(Angajat compareAng) {
        return this.nume.compareTo(compareAng.getNume());
    }
}

class AngajatComparatorById implements Comparator<Angajat> {
    public int compare(Angajat a, Angajat b){
        return a.getIdAngajat() - b.getIdAngajat();
    }
}
