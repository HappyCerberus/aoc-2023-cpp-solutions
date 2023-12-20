module;

#include <string_view>

export module input;

export namespace input {
const std::string_view day20_test = R"(broadcaster -> a
%a -> inv, con
&inv -> b
%b -> con
&con -> output)";
const std::string_view day20 = R"(%nz -> jm, ms
%xk -> cs, ks
%rh -> ks
%ml -> mf, ks
%mf -> ks, km
&ms -> lq, fm, sz
%bk -> zz, ks
%zf -> dn
%qf -> kf
%zv -> mz, ms
&tc -> mn, xf, jl, xs, zk
%hd -> dn, mm
%nv -> pn, dn
&gc -> zr
&ks -> jn, cs, cm
%vz -> pz, tc
%jl -> ps
%lq -> ms, fm
%fl -> ms
%zz -> ks, vd
%td -> bj, tc
broadcaster -> mn, jn, hd, lq
&dn -> jk, qf, gc, hf, hd, nr, mm
%vd -> ks, ml
%cp -> fl, ms
%jn -> ks, xk
%xg -> tc
%xs -> zk
%kf -> dz, dn
%qx -> ks, rh
%kb -> ms, tl
%mm -> nv
%mn -> tc, xs
%cs -> gb
%jm -> ms, cp
%bj -> tc, xx
%pn -> dn, jk
%fm -> zv
%jk -> nr
%pz -> td, tc
%xx -> tc, xg
%gb -> bk, ks
%dz -> zb, dn
%vl -> jl, tc
&sz -> zr
%gx -> ms, kb
%zb -> dn, zf
%tl -> pp, ms
%pp -> nz, ms
%km -> ks, qx
%ps -> tc, vz
%mz -> ms, gx
&cm -> zr
%hf -> qf
&zr -> rx
&xf -> zr
%nr -> hf
%zk -> vl)";
} // namespace input