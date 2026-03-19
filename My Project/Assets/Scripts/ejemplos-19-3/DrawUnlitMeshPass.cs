using Unity.Mathematics;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.RenderGraphModule;
using UnityEngine.Rendering.RenderGraphModule.Util;
using UnityEngine.Rendering.Universal;

public class DrawUnlitMeshPass : ScriptableRenderPass
{
    private Material material;
    private Mesh mesh;
    private int passId;

    class PassData
    {
        public Material material;
        public Mesh mesh;
        public int passId; // a partir del shader del material
    }

    public void Setup(Material m, Mesh me, string shaderPassName)
    {
        this.material = m; // me lo pasan desde la render feature
        this.mesh = me;
        passId = -1; // id invalido
        if ((this.material != null) && (shaderPassName.Length > 0))
        {
            // a partir del nombre conseguimos el id
            for (int i = 0; i< m.passCount; ++i )
            {
                if (m.GetPassName(i) == shaderPassName)
                {
                    this.passId = i; // hay que buscarlo a mano
                    break;
                }
            }
        }
    }

    public override void RecordRenderGraph(RenderGraph renderGraph, ContextContainer frameData)
    {
        using (var builder = renderGraph.AddRasterRenderPass<PassData>("Crear textura de color", out var passData)) // devuelve un constructor de nodo, con esto se abre y luego hay que cerrarlo
        {
            passData.material = material;
            passData.mesh = mesh;
            passData.passId = passId;

            UniversalResourceData resourceData = frameData.Get<UniversalResourceData>();

            // destino
            var destination = resourceData.activeColorTexture;
            builder.SetRenderAttachment(destination, 0);

            builder.SetRenderFunc<PassData>(ExecutePass);
        }
    }

    static void ExecutePass(PassData data, RasterGraphContext context)
    {
        var cmd = context.cmd;
        if (data.passId >= 0)
        {
            cmd.DrawMesh(data.mesh, Matrix4x4.identity, data.material, data.passId);
        }
        else
        {
            cmd.DrawMesh(data.mesh, Matrix4x4.identity, data.material);
        }
    }
}
