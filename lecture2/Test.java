class Test {
    static void foo(StringBuilder s) {
        s.append("x");
    }

    public static void main(String[] args) {
        StringBuilder a = new StringBuilder("hi");
        foo(a);
        a.append("s");
        System.out.println(a);
    }
}
