using UnityEngine.Rendering;
using UnityEngine.Rendering.RenderGraphModule;
using UnityEngine.Rendering.RenderGraphModule.Util;
using UnityEngine.Rendering.Universal;
class CopyPass : ScriptableRenderPass
{
    public CopyPass()
    {
        requiresIntermediateTexture = true;
    }

    public override void RecordRenderGraph(RenderGraph renderGraph,
    ContextContainer frameData)
    {
        // frame data es un contenedor de muchas cosas, con el get coges el objeto que sea de ese tipo (solo habrá uno)
        UniversalResourceData resourceData = frameData.Get<UniversalResourceData>();

        // la textura en la que estábamos escupiendo cosas
        var source = resourceData.activeColorTexture;

        // creamos la textura/target/destino nueva
        // le pedimos al render graph que cree una textura, un recurso que el propio render graph gestionará, será el responsable de su ciclo de vida
        var destinationDesc = renderGraph.GetTextureDesc(source);
        destinationDesc.name = $"CopyPass-Pr8-{passName}";
        TextureHandle destination = renderGraph.CreateTexture(destinationDesc);

        // creamos el nodo
        renderGraph.AddCopyPass(source, destination, passName);

        // con el render graph viewer se puede ver a CopyPass-Pr8 que usa copy pass para pintarse
    }
}