function _SortFunctionCompare(const aFirst, aSecond: _PT): Integer; inline;
_CompareFunctionBody

function _SortFunction(list: _PT): _PT;
var
	p, q, e, tail, oldhead: _PT;
	insize, nmerges, psize, qsize, i: Integer;
begin
	if 
		nil = list
	then
		result := nil
	else
	begin
		insize := 1;
		while
			True
		do
		begin
			p := list;
			oldhead := list;
			list := nil;
			tail := nil;
			nmerges := 0;
			while 
				p <> nil
			do
			begin
				Inc(nmerges);
				q := p;
				psize := 0;
				for i := 0 to insize - 1 do
				begin
					Inc(psize);
					q := q._Next;
					if 
						q = nil
					then
						break;
				end;
				qsize := insize;
				while 
					(psize > 0)
					or
					(
						(qsize > 0)
						and
						(q <> nil)
					)
				do
				begin
					if 
						0 = psize
					then
					begin
						e := q;
						q := q._Next;
						Dec(qsize);
					end
					else if
						(0 = qsize) or (nil = q)
					then
					begin
						e := p;
						p := p._Next;
						Dec(psize);
					end
					else if
						_SortFunctionCompare(p, q) <= 0
					then
					begin
						e := p;
						p := p._Next;
						Dec(psize);
					end
					else
					begin
						e := q;
						q := q._Next;
						Dec(qsize);
					end;
					if 
						tail <> nil
					then
						tail._Next := e
					else
						list := e;
					tail := e;
				end;
				p := q;
			end;
			tail._Next := nil;
			if 
				nmerges  <= 1
			then
			begin
				result := list;
				break;
			end
			else
				insize := 2 * insize;
		end;
	end;
end;
